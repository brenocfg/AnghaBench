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
 int /*<<< orphan*/  GPIO_LOW_TO_HIGH_TRANSITION ; 
 int /*<<< orphan*/  GPIO_PIN0 ; 
 int /*<<< orphan*/  GPIO_PIN1 ; 
 int GPIO_PIN5 ; 
 int GPIO_PIN6 ; 
 int /*<<< orphan*/  GPIO_PIN7 ; 
 int /*<<< orphan*/  GPIO_PORT_P1 ; 
 int /*<<< orphan*/  GPIO_PORT_P2 ; 
 int /*<<< orphan*/  GPIO_PORT_P3 ; 
 int /*<<< orphan*/  GPIO_PORT_P4 ; 
 int /*<<< orphan*/  GPIO_PRIMARY_MODULE_FUNCTION ; 
 int /*<<< orphan*/  MAP_GPIO_interruptEdgeSelect (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setAsInputPinWithPullDownResistor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_GPIO_setAsOutputPin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionInputPin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setOutputHighOnPin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_GPIO_setOutputLowOnPin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_EXP432P401R_initDMA () ; 
 int /*<<< orphan*/  SPI_init () ; 
 int /*<<< orphan*/  WiFi_init () ; 

void MSP_EXP432P401R_initWiFi(void)
{
    /* Configure EN & CS pins to disable CC3100 */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);

    /* Configure CLK, MOSI & MISO for SPI0 (EUSCI_B0) */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
        GPIO_PIN5 | GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN7,
        GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configure IRQ pin */
    MAP_GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5,
        GPIO_LOW_TO_HIGH_TRANSITION);

    /* Initialize SPI and WiFi drivers */
    MSP_EXP432P401R_initDMA();
    SPI_init();
    WiFi_init();
}