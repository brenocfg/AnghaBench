#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtc_device {int uie_unsupported; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  alarm_irq_enable; int /*<<< orphan*/  set_alarm; int /*<<< orphan*/  read_alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_2__*,int) ; 
 struct rtc_device* devm_rtc_device_register (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 int /*<<< orphan*/  opal_get_tpo_time ; 
 TYPE_1__ opal_rtc_ops ; 
 int /*<<< orphan*/  opal_set_tpo_time ; 
 int /*<<< orphan*/  opal_tpo_alarm_irq_enable ; 

__attribute__((used)) static int opal_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtc;

	if (pdev->dev.of_node &&
	    (of_property_read_bool(pdev->dev.of_node, "wakeup-source") ||
	     of_property_read_bool(pdev->dev.of_node, "has-tpo")/* legacy */)) {
		device_set_wakeup_capable(&pdev->dev, true);
		opal_rtc_ops.read_alarm	= opal_get_tpo_time;
		opal_rtc_ops.set_alarm = opal_set_tpo_time;
		opal_rtc_ops.alarm_irq_enable = opal_tpo_alarm_irq_enable;
	}

	rtc = devm_rtc_device_register(&pdev->dev, DRVNAME, &opal_rtc_ops,
				       THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	rtc->uie_unsupported = 1;

	return 0;
}