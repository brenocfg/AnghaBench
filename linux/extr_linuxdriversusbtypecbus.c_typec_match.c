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
struct typec_device_id {scalar_t__ svid; scalar_t__ mode; } ;
struct typec_altmode_driver {struct typec_device_id* id_table; } ;
struct typec_altmode {scalar_t__ svid; scalar_t__ mode; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPEC_ANY_MODE ; 
 struct typec_altmode_driver* to_altmode_driver (struct device_driver*) ; 
 struct typec_altmode* to_typec_altmode (struct device*) ; 

__attribute__((used)) static int typec_match(struct device *dev, struct device_driver *driver)
{
	struct typec_altmode_driver *drv = to_altmode_driver(driver);
	struct typec_altmode *altmode = to_typec_altmode(dev);
	const struct typec_device_id *id;

	for (id = drv->id_table; id->svid; id++)
		if (id->svid == altmode->svid &&
		    (id->mode == TYPEC_ANY_MODE || id->mode == altmode->mode))
			return 1;
	return 0;
}