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
struct uuid_module {int max_instance; int* instance_id; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int skl_get_pvtid_map(struct uuid_module *module, int instance_id)
{
	int pvt_id;

	for (pvt_id = 0; pvt_id < module->max_instance; pvt_id++) {
		if (module->instance_id[pvt_id] == instance_id)
			return pvt_id;
	}
	return -EINVAL;
}