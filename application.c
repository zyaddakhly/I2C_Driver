/* 
 * File:   application.c
 * Author: zyadi
 *
 * Created on August 18, 2023, 8:01 AM
 */

/*---------------------------Section Include-----------------------------------------------*/
#include "application.h"


#define SLAVE1 0x60
#define SLAVE2 0x62

/*---------------------------Function Declaration -----------------------------------------------*/
void application_init(void);
void send_byte(uint8 addresse,uint8 data);
/*--------------------------- Global Variable -----------------------------------------------*/
Std_ReturnType ret;
uint8 ack;

void MSSP_INT(void);
volatile uint8 Counter1;
volatile uint8 i2c_slave_data;
mssp_i2c_t i2c_obj = 
{
    .i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS,
    .i2c_cfg.i2c_slave_address = SLAVE2,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE ,
    .I2C_Report_DefaultInterruptHandler = MSSP_INT,
    .I2C_Report_Write_Collision = NULL,
    .I2C_Report_Receieve_Overflow = NULL,
    
};

int main() {
    application_init();
    ret = MSSP_I2C_Init( &i2c_obj);
   
     


    while(1)
    {


    }
  


    return 0;
}



void application_init(void)
{
    Std_ReturnType ret = E_OK;
    ecu_initialize();


}



void MSSP_INT(void)
{
    I2C_CLOCK_STRETCH_ENABLE();
    if(SSPSTATbits.R_nW == 0 && (SSPSTATbits.D_nA == 0))
    {
        uint8 buffer_addresse = SSPBUF;
        while(!SSPSTATbits.BF);
        i2c_slave_data = SSPBUF;
        if(i2c_slave_data == 'b')
        {
            led_toggle(&led);
        }
        else if(i2c_slave_data == 'd')
        {

        }
    }
    else if(SSPSTATbits.R_nW == 0)
    {
        
    }
    I2C_CLOCK_STRETCH_DISABLE();
    
    
}