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
struct tahvo_usb {int tahvo_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  TAHVO_MODE_HOST 129 
#define  TAHVO_MODE_PERIPHERAL 128 
 struct tahvo_usb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t otg_mode_show(struct device *device,
			     struct device_attribute *attr, char *buf)
{
	struct tahvo_usb *tu = dev_get_drvdata(device);

	switch (tu->tahvo_mode) {
	case TAHVO_MODE_HOST:
		return sprintf(buf, "host\n");
	case TAHVO_MODE_PERIPHERAL:
		return sprintf(buf, "peripheral\n");
	}

	return -EINVAL;
}