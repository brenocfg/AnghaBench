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
struct smb347_charger {int charging_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ enable_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_A ; 
 int /*<<< orphan*/  CMD_A_CHG_ENABLED ; 
 scalar_t__ SMB347_CHG_ENABLE_SW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smb347_charging_set(struct smb347_charger *smb, bool enable)
{
	int ret = 0;

	if (smb->pdata->enable_control != SMB347_CHG_ENABLE_SW) {
		dev_dbg(smb->dev, "charging enable/disable in SW disabled\n");
		return 0;
	}

	mutex_lock(&smb->lock);
	if (smb->charging_enabled != enable) {
		ret = regmap_update_bits(smb->regmap, CMD_A, CMD_A_CHG_ENABLED,
					 enable ? CMD_A_CHG_ENABLED : 0);
		if (!ret)
			smb->charging_enabled = enable;
	}
	mutex_unlock(&smb->lock);
	return ret;
}