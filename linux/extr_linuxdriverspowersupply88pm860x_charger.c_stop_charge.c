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
struct pm860x_charger_info {scalar_t__ online; int /*<<< orphan*/  i2c; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC1_MODE_OFF ; 
 int CHARGE_THRESHOLD ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_vbatt_threshold (struct pm860x_charger_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_charge(struct pm860x_charger_info *info, int vbatt)
{
	dev_dbg(info->dev, "Stop charging!\n");
	pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3, CC1_MODE_OFF);
	if (vbatt > CHARGE_THRESHOLD && info->online)
		set_vbatt_threshold(info, CHARGE_THRESHOLD, 0);
}