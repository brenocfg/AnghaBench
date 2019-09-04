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
typedef  int u8 ;
struct lp872x_dvs {int gpio; int init_state; } ;
struct lp872x {int dvs_pin; size_t chipid; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
typedef  enum lp872x_dvs_state { ____Placeholder_lp872x_dvs_state } lp872x_dvs_state ;
struct TYPE_2__ {struct lp872x_dvs* dvs; } ;

/* Variables and functions */
 int LP8720_DEFAULT_DVS ; 
 int LP8720_EXT_DVS_M ; 
 int LP8725_DEFAULT_DVS ; 
 int LP8725_DVS1_M ; 
 int LP8725_DVS2_M ; 
 int /*<<< orphan*/  LP872X_GENERAL_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int lp872x_update_bits (struct lp872x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lp872x_init_dvs(struct lp872x *lp)
{
	int ret, gpio;
	struct lp872x_dvs *dvs = lp->pdata ? lp->pdata->dvs : NULL;
	enum lp872x_dvs_state pinstate;
	u8 mask[] = { LP8720_EXT_DVS_M, LP8725_DVS1_M | LP8725_DVS2_M };
	u8 default_dvs_mode[] = { LP8720_DEFAULT_DVS, LP8725_DEFAULT_DVS };

	if (!dvs)
		goto set_default_dvs_mode;

	gpio = dvs->gpio;
	if (!gpio_is_valid(gpio))
		goto set_default_dvs_mode;

	pinstate = dvs->init_state;
	ret = devm_gpio_request_one(lp->dev, gpio, pinstate, "LP872X DVS");
	if (ret) {
		dev_err(lp->dev, "gpio request err: %d\n", ret);
		return ret;
	}

	lp->dvs_pin = pinstate;

	return 0;

set_default_dvs_mode:
	return lp872x_update_bits(lp, LP872X_GENERAL_CFG, mask[lp->chipid],
				default_dvs_mode[lp->chipid]);
}