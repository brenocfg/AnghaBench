#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pendsv_dispatch_t ;
struct TYPE_2__ {int /*<<< orphan*/  ICSR; } ;

/* Variables and functions */
 TYPE_1__* SCB ; 
 int /*<<< orphan*/  SCB_ICSR_PENDSVSET_Msk ; 
 int pendsv_dispatch_active ; 
 int /*<<< orphan*/ * pendsv_dispatch_table ; 

void pendsv_schedule_dispatch(size_t slot, pendsv_dispatch_t f) {
    pendsv_dispatch_table[slot] = f;
    pendsv_dispatch_active = true;
    SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}