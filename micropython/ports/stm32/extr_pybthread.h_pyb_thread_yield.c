#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ICSR; } ;
struct TYPE_3__ {struct TYPE_3__* run_next; } ;

/* Variables and functions */
 TYPE_2__* SCB ; 
 int /*<<< orphan*/  SCB_ICSR_PENDSVSET_Msk ; 
 int /*<<< orphan*/  __WFI () ; 
 TYPE_1__* pyb_thread_cur ; 

__attribute__((used)) static inline void pyb_thread_yield(void) {
    if (pyb_thread_cur->run_next == pyb_thread_cur) {
        __WFI();
    } else {
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
    }
}