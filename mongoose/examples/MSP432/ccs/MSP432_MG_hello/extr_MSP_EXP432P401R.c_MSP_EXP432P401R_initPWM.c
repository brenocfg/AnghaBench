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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int GPIO_PIN1 ; 
 int GPIO_PIN2 ; 
 int /*<<< orphan*/  GPIO_PORT_P2 ; 
 int /*<<< orphan*/  GPIO_PRIMARY_MODULE_FUNCTION ; 
 int /*<<< orphan*/  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_PMAP_configurePorts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_DISABLE_RECONFIGURATION ; 
 int /*<<< orphan*/  PMAP_P2MAP ; 
 int /*<<< orphan*/  const PM_NONE ; 
 int /*<<< orphan*/  const PM_TA1CCR1A ; 
 int /*<<< orphan*/  const PM_TA1CCR2A ; 
 int /*<<< orphan*/  PWM_init () ; 

void MSP_EXP432P401R_initPWM(void)
{
    /* Use Port Map on Port2 get Timer outputs on pins with LEDs (2.1, 2.2) */
    const uint8_t portMap [] = {
        PM_NONE, PM_TA1CCR1A, PM_TA1CCR2A, PM_NONE,
        PM_NONE, PM_NONE,     PM_NONE,     PM_NONE
    };

    /* Mapping capture compare registers to Port 2 */
    MAP_PMAP_configurePorts((const uint8_t *) portMap, PMAP_P2MAP, 1,
        PMAP_DISABLE_RECONFIGURATION);

    /* Enable PWM output on GPIO pins */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
        GPIO_PIN1 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);

    PWM_init();
}