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
 int GPIO_PIN2 ; 
 int GPIO_PIN3 ; 
 int /*<<< orphan*/  GPIO_PORT_P1 ; 
 int /*<<< orphan*/  GPIO_PORT_P3 ; 
 int /*<<< orphan*/  GPIO_PRIMARY_MODULE_FUNCTION ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionInputPin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_init () ; 

void MSP_EXP432P401R_initUART(void)
{
    /* Set P1.2 & P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Set P3.2 & P3.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Initialize the UART driver */
    UART_init();
}