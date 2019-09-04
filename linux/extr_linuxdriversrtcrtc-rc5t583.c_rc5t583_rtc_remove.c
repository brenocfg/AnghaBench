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
struct rc5t583_rtc {TYPE_1__* rtc; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rc5t583_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rc5t583_rtc_alarm_irq_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc5t583_rtc_remove(struct platform_device *pdev)
{
	struct rc5t583_rtc *rc5t583_rtc = platform_get_drvdata(pdev);

	rc5t583_rtc_alarm_irq_enable(&rc5t583_rtc->rtc->dev, 0);
	return 0;
}