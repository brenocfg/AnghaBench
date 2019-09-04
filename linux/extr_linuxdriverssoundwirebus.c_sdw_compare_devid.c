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
struct sdw_slave_id {scalar_t__ unique_id; scalar_t__ mfg_id; scalar_t__ part_id; scalar_t__ class_id; } ;
struct TYPE_2__ {scalar_t__ unique_id; scalar_t__ mfg_id; scalar_t__ part_id; scalar_t__ class_id; } ;
struct sdw_slave {TYPE_1__ id; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int sdw_compare_devid(struct sdw_slave *slave, struct sdw_slave_id id)
{

	if ((slave->id.unique_id != id.unique_id) ||
	    (slave->id.mfg_id != id.mfg_id) ||
	    (slave->id.part_id != id.part_id) ||
	    (slave->id.class_id != id.class_id))
		return -ENODEV;

	return 0;
}