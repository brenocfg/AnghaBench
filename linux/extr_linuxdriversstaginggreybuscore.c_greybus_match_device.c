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
struct greybus_driver {int /*<<< orphan*/  id_table; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_bundle {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct greybus_bundle_id* greybus_match_id (struct gb_bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gb_bundle (struct device*) ; 
 struct gb_bundle* to_gb_bundle (struct device*) ; 
 struct greybus_driver* to_greybus_driver (struct device_driver*) ; 

__attribute__((used)) static int greybus_match_device(struct device *dev, struct device_driver *drv)
{
	struct greybus_driver *driver = to_greybus_driver(drv);
	struct gb_bundle *bundle;
	const struct greybus_bundle_id *id;

	if (!is_gb_bundle(dev))
		return 0;

	bundle = to_gb_bundle(dev);

	id = greybus_match_id(bundle, driver->id_table);
	if (id)
		return 1;
	/* FIXME - Dynamic ids? */
	return 0;
}