#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; struct lp8755_chip* driver_data; TYPE_2__* dev; int /*<<< orphan*/  regmap; } ;
struct lp8755_platform_data {int /*<<< orphan*/ * buck_data; } ;
struct lp8755_chip {size_t mphase; TYPE_2__* dev; int /*<<< orphan*/ ** rdev; int /*<<< orphan*/  regmap; struct lp8755_platform_data* pdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int nreg; int* buck_num; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * devm_regulator_register (TYPE_2__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/ * lp8755_regulators ; 
 TYPE_1__* mphase_buck ; 

__attribute__((used)) static int lp8755_regulator_init(struct lp8755_chip *pchip)
{
	int ret, icnt, buck_num;
	struct lp8755_platform_data *pdata = pchip->pdata;
	struct regulator_config rconfig = { };

	rconfig.regmap = pchip->regmap;
	rconfig.dev = pchip->dev;
	rconfig.driver_data = pchip;

	for (icnt = 0; icnt < mphase_buck[pchip->mphase].nreg; icnt++) {
		buck_num = mphase_buck[pchip->mphase].buck_num[icnt];
		rconfig.init_data = pdata->buck_data[buck_num];
		rconfig.of_node = pchip->dev->of_node;
		pchip->rdev[buck_num] =
		    devm_regulator_register(pchip->dev,
				    &lp8755_regulators[buck_num], &rconfig);
		if (IS_ERR(pchip->rdev[buck_num])) {
			ret = PTR_ERR(pchip->rdev[buck_num]);
			pchip->rdev[buck_num] = NULL;
			dev_err(pchip->dev, "regulator init failed: buck %d\n",
				buck_num);
			return ret;
		}
	}

	return 0;
}