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
struct TYPE_2__ {scalar_t__ mfg_id; scalar_t__ part_id; } ;
struct sdw_slave {TYPE_1__ id; } ;
struct sdw_driver {struct sdw_device_id* id_table; } ;
struct sdw_device_id {scalar_t__ mfg_id; scalar_t__ part_id; } ;

/* Variables and functions */

__attribute__((used)) static const struct sdw_device_id *
sdw_get_device_id(struct sdw_slave *slave, struct sdw_driver *drv)
{
	const struct sdw_device_id *id = drv->id_table;

	while (id && id->mfg_id) {
		if (slave->id.mfg_id == id->mfg_id &&
		    slave->id.part_id == id->part_id)
			return id;
		id++;
	}

	return NULL;
}