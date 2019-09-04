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
struct tps80031_regulator_platform_data {int ext_ctrl_flag; } ;
struct tps80031_regulator {TYPE_1__* rinfo; int /*<<< orphan*/  dev; int /*<<< orphan*/  ext_ctrl_flag; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ preq_bit; int /*<<< orphan*/  trans_reg; int /*<<< orphan*/  state_reg; } ;

/* Variables and functions */
 int TPS80031_PWR_ON_ON_SLEEP ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int /*<<< orphan*/  TPS80031_TRANS_SLEEP_MASK ; 
 int /*<<< orphan*/  TPS80031_TRANS_SLEEP_ON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int tps80031_ext_power_req_config (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps80031_update (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps80031_power_req_config(struct device *parent,
		struct tps80031_regulator *ri,
		struct tps80031_regulator_platform_data *tps80031_pdata)
{
	int ret = 0;

	if (ri->rinfo->preq_bit < 0)
		goto skip_pwr_req_config;

	ret = tps80031_ext_power_req_config(parent, ri->ext_ctrl_flag,
			ri->rinfo->preq_bit, ri->rinfo->state_reg,
			ri->rinfo->trans_reg);
	if (ret < 0) {
		dev_err(ri->dev, "ext powerreq config failed, err = %d\n", ret);
		return ret;
	}

skip_pwr_req_config:
	if (tps80031_pdata->ext_ctrl_flag & TPS80031_PWR_ON_ON_SLEEP) {
		ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				ri->rinfo->trans_reg, TPS80031_TRANS_SLEEP_ON,
				TPS80031_TRANS_SLEEP_MASK);
		if (ret < 0) {
			dev_err(ri->dev, "Reg 0x%02x update failed, e %d\n",
					ri->rinfo->trans_reg, ret);
			return ret;
		}
	}
	return ret;
}