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
struct uwb_rc {int dummy; } ;
struct uwb_dev {struct uwb_rc* rc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int sscanf (char const*,char*,int*) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 
 int uwb_radio_force_channel (struct uwb_rc*,int) ; 

__attribute__((used)) static ssize_t uwb_rc_beacon_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t size)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);
	struct uwb_rc *rc = uwb_dev->rc;
	int channel;
	ssize_t result = -EINVAL;

	result = sscanf(buf, "%d", &channel);
	if (result >= 1)
		result = uwb_radio_force_channel(rc, channel);

	return result < 0 ? result : size;
}