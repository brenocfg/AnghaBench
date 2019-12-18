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
 int /*<<< orphan*/  IRQ_PRI_PENDSV ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PendSV_IRQn ; 
 int pendsv_dispatch_active ; 

void pendsv_init(void) {
    #if defined(PENDSV_DISPATCH_NUM_SLOTS)
    pendsv_dispatch_active = false;
    #endif
    // set PendSV interrupt at lowest priority
    NVIC_SetPriority(PendSV_IRQn, IRQ_PRI_PENDSV);
}