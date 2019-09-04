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
struct act8865_regulator_data {int id; } ;
struct act8865_platform_data {int num_regulators; struct act8865_regulator_data* regulators; } ;

/* Variables and functions */

__attribute__((used)) static struct act8865_regulator_data *act8865_get_regulator_data(
		int id, struct act8865_platform_data *pdata)
{
	int i;

	if (!pdata)
		return NULL;

	for (i = 0; i < pdata->num_regulators; i++) {
		if (pdata->regulators[i].id == id)
			return &pdata->regulators[i];
	}

	return NULL;
}