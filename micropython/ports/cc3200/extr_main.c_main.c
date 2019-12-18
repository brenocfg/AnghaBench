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
typedef  int /*<<< orphan*/ * OsiTaskHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_SystemInit () ; 
 int /*<<< orphan*/  MICROPY_TASK_PRIORITY ; 
 int /*<<< orphan*/  MICROPY_TASK_STACK_LEN ; 
 int /*<<< orphan*/  TASK_MicroPython ; 
 int /*<<< orphan*/  antenna_init0 () ; 
 int /*<<< orphan*/  mpTaskStack ; 
 int /*<<< orphan*/  mpTaskTCB ; 
 int /*<<< orphan*/  osi_start () ; 
 int /*<<< orphan*/  pybwdt_init0 () ; 
 int /*<<< orphan*/ * xTaskCreateStatic (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__ ((section (".boot")))
int main (void) {

    // Initialize the clocks and the interrupt system
    HAL_SystemInit();

#if MICROPY_HW_ANTENNA_DIVERSITY
    // configure the antenna selection pins
    antenna_init0();
#endif

    // Init the watchdog
    pybwdt_init0();

#ifndef DEBUG
    OsiTaskHandle mpTaskHandle;
#endif
    mpTaskHandle = xTaskCreateStatic(TASK_MicroPython, "MicroPy",
        MICROPY_TASK_STACK_LEN, NULL, MICROPY_TASK_PRIORITY, mpTaskStack, &mpTaskTCB);
    ASSERT(mpTaskHandle != NULL);

    osi_start();

    for ( ; ; );
}