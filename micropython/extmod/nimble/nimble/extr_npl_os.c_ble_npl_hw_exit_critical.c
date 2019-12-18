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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CRIT_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_irq_pri (scalar_t__) ; 

void ble_npl_hw_exit_critical(uint32_t ctx) {
    DEBUG_CRIT_printf("ble_npl_hw_exit_critical(%u)\n", (uint)ctx);
    restore_irq_pri(ctx);
}