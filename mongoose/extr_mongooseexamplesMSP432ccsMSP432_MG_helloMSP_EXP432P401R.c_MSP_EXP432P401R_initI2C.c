#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GPIO_PIN6 ; 
 int GPIO_PIN7 ; 
 int /*<<< orphan*/  GPIO_PORT_P1 ; 
 int /*<<< orphan*/  GPIO_PRIMARY_MODULE_FUNCTION ; 
 int /*<<< orphan*/  I2C_init () ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionInputPin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void MSP_EXP432P401R_initI2C(void)
{
    /*
     * NOTE: TI-RTOS examples configure EUSCIB0 as either SPI or I2C.  Thus,
     * a conflict occurs when the I2C & SPI drivers are used simultaneously in
     * an application.  Modify the pin mux settings in this file and resolve the
     * conflict before running your the application.
     */
    /* Configure Pins 1.6 & 1.7 as SDA & SCL, respectively. */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Initialize the I2C driver */
    I2C_init();
}