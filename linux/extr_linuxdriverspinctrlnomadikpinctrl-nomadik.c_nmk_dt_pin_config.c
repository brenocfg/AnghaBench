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
struct TYPE_2__ {unsigned long* choice; unsigned long config; int size; } ;

/* Variables and functions */
 TYPE_1__* nmk_cfg_params ; 

__attribute__((used)) static int nmk_dt_pin_config(int index, int val, unsigned long *config)
{
	int ret = 0;

	if (nmk_cfg_params[index].choice == NULL)
		*config = nmk_cfg_params[index].config;
	else {
		/* test if out of range */
		if  (val < nmk_cfg_params[index].size) {
			*config = nmk_cfg_params[index].config |
				nmk_cfg_params[index].choice[val];
		}
	}
	return ret;
}