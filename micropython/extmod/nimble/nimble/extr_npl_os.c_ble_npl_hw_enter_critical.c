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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CRIT_printf (char*) ; 
 int /*<<< orphan*/  raise_irq_pri (int) ; 

uint32_t ble_npl_hw_enter_critical(void) {
    DEBUG_CRIT_printf("ble_npl_hw_enter_critical()\n");
    return raise_irq_pri(15);
}