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
struct regulator_init_data {int dummy; } ;
struct lp872x_platform_data {TYPE_1__* regulator_data; } ;
struct lp872x {int num_regulators; struct lp872x_platform_data* pdata; } ;
struct TYPE_2__ {int id; struct regulator_init_data* init_data; } ;

/* Variables and functions */

__attribute__((used)) static struct regulator_init_data
*lp872x_find_regulator_init_data(int id, struct lp872x *lp)
{
	struct lp872x_platform_data *pdata = lp->pdata;
	int i;

	if (!pdata)
		return NULL;

	for (i = 0; i < lp->num_regulators; i++) {
		if (pdata->regulator_data[i].id == id)
			return pdata->regulator_data[i].init_data;
	}

	return NULL;
}