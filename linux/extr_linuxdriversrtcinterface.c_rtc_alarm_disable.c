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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_2__ dev; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* alarm_irq_enable ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rtc_alarm_irq_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc_alarm_disable(struct rtc_device *rtc)
{
	if (!rtc->ops || !rtc->ops->alarm_irq_enable)
		return;

	rtc->ops->alarm_irq_enable(rtc->dev.parent, false);
	trace_rtc_alarm_irq_enable(0, 0);
}