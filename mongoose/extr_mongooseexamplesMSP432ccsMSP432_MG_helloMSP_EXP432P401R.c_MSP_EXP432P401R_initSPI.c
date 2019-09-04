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
 int GPIO_PIN5 ; 
 int GPIO_PIN6 ; 
 int /*<<< orphan*/  GPIO_PIN7 ; 
 int /*<<< orphan*/  GPIO_PORT_P1 ; 
 int /*<<< orphan*/  GPIO_PORT_P3 ; 
 int /*<<< orphan*/  GPIO_PRIMARY_MODULE_FUNCTION ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionInputPin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_EXP432P401R_initDMA () ; 
 int /*<<< orphan*/  SPI_init () ; 

void MSP_EXP432P401R_initSPI(void)
{
    /*
     * NOTE: TI-RTOS examples configure EUSCIB0 as either SPI or I2C.  Thus,
     * a conflict occurs when the I2C & SPI drivers are used simultaneously in
     * an application.  Modify the pin mux settings in this file and resolve the
     * conflict before running your the application.
     */
    /* Configure CLK, MOSI & MISO for SPI0 (EUSCI_B0) */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
        GPIO_PIN5 | GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN7,
        GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configure CLK, MOSI & MISO for SPI1 (EUSCI_B2) */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3,
        GPIO_PIN5 | GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN7,
        GPIO_PRIMARY_MODULE_FUNCTION);

    MSP_EXP432P401R_initDMA();
    SPI_init();
}