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
struct TYPE_2__ {int min_uV; } ;
struct da903x_regulator_info {int max_uV; TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int check_range(struct da903x_regulator_info *info,
				int min_uV, int max_uV)
{
	if (min_uV < info->desc.min_uV || min_uV > info->max_uV)
		return -EINVAL;

	return 0;
}