#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  devt; } ;
struct rtc_device {int registered; TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  char_dev; struct module* owner; int /*<<< orphan*/  ops; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int __rtc_read_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_dev_prepare (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_device_get_offset (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_initialize_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  rtc_proc_add_device (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_valid_tm (int /*<<< orphan*/ *) ; 

int __rtc_register_device(struct module *owner, struct rtc_device *rtc)
{
	struct rtc_wkalrm alrm;
	int err;

	if (!rtc->ops)
		return -EINVAL;

	rtc->owner = owner;
	rtc_device_get_offset(rtc);

	/* Check to see if there is an ALARM already set in hw */
	err = __rtc_read_alarm(rtc, &alrm);
	if (!err && !rtc_valid_tm(&alrm.time))
		rtc_initialize_alarm(rtc, &alrm);

	rtc_dev_prepare(rtc);

	err = cdev_device_add(&rtc->char_dev, &rtc->dev);
	if (err)
		dev_warn(rtc->dev.parent, "failed to add char device %d:%d\n",
			 MAJOR(rtc->dev.devt), rtc->id);
	else
		dev_dbg(rtc->dev.parent, "char device (%d:%d)\n",
			MAJOR(rtc->dev.devt), rtc->id);

	rtc_proc_add_device(rtc);

	rtc->registered = true;
	dev_info(rtc->dev.parent, "registered as %s\n",
		 dev_name(&rtc->dev));

	return 0;
}