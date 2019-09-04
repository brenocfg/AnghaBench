#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct TYPE_7__ {int /*<<< orphan*/  devt; struct device* parent; } ;
struct rtc_device {int id; TYPE_1__ dev; int /*<<< orphan*/  char_dev; struct module* owner; struct rtc_class_ops const* ops; } ;
struct rtc_class_ops {int dummy; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct rtc_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int __rtc_read_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 struct rtc_device* rtc_allocate_device () ; 
 int /*<<< orphan*/  rtc_dev_prepare (struct rtc_device*) ; 
 int rtc_device_get_id (struct device*) ; 
 int /*<<< orphan*/  rtc_device_get_offset (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_ida ; 
 int /*<<< orphan*/  rtc_initialize_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  rtc_proc_add_device (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_valid_tm (int /*<<< orphan*/ *) ; 

struct rtc_device *rtc_device_register(const char *name, struct device *dev,
					const struct rtc_class_ops *ops,
					struct module *owner)
{
	struct rtc_device *rtc;
	struct rtc_wkalrm alrm;
	int id, err;

	id = rtc_device_get_id(dev);
	if (id < 0) {
		err = id;
		goto exit;
	}

	rtc = rtc_allocate_device();
	if (!rtc) {
		err = -ENOMEM;
		goto exit_ida;
	}

	rtc->id = id;
	rtc->ops = ops;
	rtc->owner = owner;
	rtc->dev.parent = dev;

	dev_set_name(&rtc->dev, "rtc%d", id);

	rtc_device_get_offset(rtc);

	/* Check to see if there is an ALARM already set in hw */
	err = __rtc_read_alarm(rtc, &alrm);

	if (!err && !rtc_valid_tm(&alrm.time))
		rtc_initialize_alarm(rtc, &alrm);

	rtc_dev_prepare(rtc);

	err = cdev_device_add(&rtc->char_dev, &rtc->dev);
	if (err) {
		dev_warn(&rtc->dev, "%s: failed to add char device %d:%d\n",
			 name, MAJOR(rtc->dev.devt), rtc->id);

		/* This will free both memory and the ID */
		put_device(&rtc->dev);
		goto exit;
	} else {
		dev_dbg(&rtc->dev, "%s: dev (%d:%d)\n", name,
			MAJOR(rtc->dev.devt), rtc->id);
	}

	rtc_proc_add_device(rtc);

	dev_info(dev, "rtc core: registered %s as %s\n",
			name, dev_name(&rtc->dev));

	return rtc;

exit_ida:
	ida_simple_remove(&rtc_ida, id);

exit:
	dev_err(dev, "rtc core: unable to register %s, err = %d\n",
			name, err);
	return ERR_PTR(err);
}