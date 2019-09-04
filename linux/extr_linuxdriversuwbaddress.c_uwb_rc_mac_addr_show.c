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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct uwb_mac_addr {int dummy; } ;
struct uwb_dev {struct uwb_rc* rc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_ADDR_MAC ; 
 int /*<<< orphan*/  UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 
 scalar_t__ uwb_mac_addr_print (char*,int /*<<< orphan*/ ,struct uwb_mac_addr*) ; 
 scalar_t__ uwb_rc_addr_get (struct uwb_rc*,struct uwb_mac_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uwb_rc_mac_addr_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);
	struct uwb_rc *rc = uwb_dev->rc;
	struct uwb_mac_addr addr;
	ssize_t result;

	mutex_lock(&rc->uwb_dev.mutex);
	result = uwb_rc_addr_get(rc, &addr, UWB_ADDR_MAC);
	mutex_unlock(&rc->uwb_dev.mutex);
	if (result >= 0) {
		result = uwb_mac_addr_print(buf, UWB_ADDR_STRSIZE, &addr);
		buf[result++] = '\n';
	}
	return result;
}