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
struct gbphy_driver {struct gbphy_device_id* id_table; } ;
struct gbphy_device_id {scalar_t__ protocol_id; } ;
struct gbphy_device {TYPE_1__* cport_desc; } ;
struct TYPE_2__ {scalar_t__ protocol_id; } ;

/* Variables and functions */

__attribute__((used)) static const struct gbphy_device_id *
gbphy_dev_match_id(struct gbphy_device *gbphy_dev,
		   struct gbphy_driver *gbphy_drv)
{
	const struct gbphy_device_id *id = gbphy_drv->id_table;

	if (!id)
		return NULL;

	for (; id->protocol_id; id++)
		if (id->protocol_id == gbphy_dev->cport_desc->protocol_id)
			return id;

	return NULL;
}