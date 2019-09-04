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
struct twl4030_bci {int ac_mode; int usb_mode; TYPE_1__* ac; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct twl4030_bci* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modes ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 int twl4030_charger_enable_ac (struct twl4030_bci*,int) ; 
 int twl4030_charger_enable_usb (struct twl4030_bci*,int) ; 

__attribute__((used)) static ssize_t
twl4030_bci_mode_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t n)
{
	struct twl4030_bci *bci = dev_get_drvdata(dev->parent);
	int mode;
	int status;

	mode = sysfs_match_string(modes, buf);
	if (mode < 0)
		return mode;

	if (dev == &bci->ac->dev) {
		if (mode == 2)
			return -EINVAL;
		twl4030_charger_enable_ac(bci, false);
		bci->ac_mode = mode;
		status = twl4030_charger_enable_ac(bci, true);
	} else {
		twl4030_charger_enable_usb(bci, false);
		bci->usb_mode = mode;
		status = twl4030_charger_enable_usb(bci, true);
	}
	return (status == 0) ? n : status;
}