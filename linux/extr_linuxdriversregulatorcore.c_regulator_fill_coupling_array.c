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
struct coupling_desc {int n_coupled; int n_resolved; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {struct coupling_desc coupling_desc; } ;

/* Variables and functions */
 struct regulator_dev* of_parse_coupled_regulator (struct regulator_dev*,int) ; 

__attribute__((used)) static int regulator_fill_coupling_array(struct regulator_dev *rdev)
{
	struct coupling_desc *c_desc = &rdev->coupling_desc;
	int n_coupled = c_desc->n_coupled;
	struct regulator_dev *c_rdev;
	int i;

	for (i = 1; i < n_coupled; i++) {
		/* already resolved */
		if (c_desc->coupled_rdevs[i])
			continue;

		c_rdev = of_parse_coupled_regulator(rdev, i - 1);

		if (c_rdev) {
			c_desc->coupled_rdevs[i] = c_rdev;
			c_desc->n_resolved++;
		}
	}

	if (rdev->coupling_desc.n_resolved < n_coupled)
		return -1;
	else
		return 0;
}