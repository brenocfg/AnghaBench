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
struct twl_rtc {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_TIMER_M ; 
 int /*<<< orphan*/  mask_rtc_irq_bit (struct twl_rtc*,int /*<<< orphan*/ ) ; 
 struct twl_rtc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void twl_rtc_shutdown(struct platform_device *pdev)
{
	struct twl_rtc *twl_rtc = platform_get_drvdata(pdev);

	/* mask timer interrupts, but leave alarm interrupts on to enable
	   power-on when alarm is triggered */
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
}