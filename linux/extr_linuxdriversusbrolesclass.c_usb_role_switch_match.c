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
struct device_connection {int /*<<< orphan*/ * endpoint; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __switch_match ; 
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  role_class ; 
 void* to_role_switch (struct device*) ; 

__attribute__((used)) static void *usb_role_switch_match(struct device_connection *con, int ep,
				   void *data)
{
	struct device *dev;

	dev = class_find_device(role_class, NULL, con->endpoint[ep],
				__switch_match);

	return dev ? to_role_switch(dev) : ERR_PTR(-EPROBE_DEFER);
}