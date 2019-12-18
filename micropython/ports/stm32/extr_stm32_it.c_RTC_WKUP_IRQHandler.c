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
struct TYPE_2__ {int /*<<< orphan*/  ISR; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTI_RTC_WAKEUP ; 
 int /*<<< orphan*/  Handle_EXTI_Irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EXIT (int /*<<< orphan*/ ) ; 
 TYPE_1__* RTC ; 
 int /*<<< orphan*/  RTC_ISR_WUTF ; 
 int /*<<< orphan*/  RTC_WKUP_IRQn ; 

void RTC_WKUP_IRQHandler(void) {
    IRQ_ENTER(RTC_WKUP_IRQn);
    RTC->ISR &= ~RTC_ISR_WUTF; // clear wakeup interrupt flag
    Handle_EXTI_Irq(EXTI_RTC_WAKEUP); // clear EXTI flag and execute optional callback
    IRQ_EXIT(RTC_WKUP_IRQn);
}