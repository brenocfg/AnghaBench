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
struct da9052_regulator_info {int max_uV; int min_uV; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int verify_range(struct da9052_regulator_info *info,
			 int min_uV, int max_uV)
{
	if (min_uV > info->max_uV || max_uV < info->min_uV)
		return -EINVAL;

	return 0;
}