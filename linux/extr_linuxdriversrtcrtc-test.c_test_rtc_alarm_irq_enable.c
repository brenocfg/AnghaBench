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
struct rtc_test_data {unsigned int alarm_en; int /*<<< orphan*/  alarm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct rtc_test_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int test_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct rtc_test_data *rtd = dev_get_drvdata(dev);

	rtd->alarm_en = enable;
	if (enable)
		add_timer(&rtd->alarm);
	else
		del_timer(&rtd->alarm);

	return 0;
}