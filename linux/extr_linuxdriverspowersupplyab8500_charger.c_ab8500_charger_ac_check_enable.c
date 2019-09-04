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
struct ux500_charger {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  charger_connected; } ;
struct ab8500_charger {int /*<<< orphan*/  dev; int /*<<< orphan*/  usb_chg; TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_CHARGER ; 
 int /*<<< orphan*/  AB8500_CHARGER_CTRL ; 
 int /*<<< orphan*/  AB8500_MCH_CTRL1 ; 
 int /*<<< orphan*/  DROP_COUNT_RESET ; 
 int MAIN_CH_ENA ; 
 int ab8500_charger_ac_en (int /*<<< orphan*/ *,int,int,int) ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct ab8500_charger* to_ab8500_charger_ac_device_info (struct ux500_charger*) ; 

__attribute__((used)) static int ab8500_charger_ac_check_enable(struct ux500_charger *charger,
	int vset, int iset)
{
	u8 mainch_ctrl1 = 0;
	int ret = 0;

	struct ab8500_charger *di = to_ab8500_charger_ac_device_info(charger);

	if (!di->ac.charger_connected)
		return ret;

	ret = abx500_get_register_interruptible(di->dev, AB8500_CHARGER,
				AB8500_MCH_CTRL1, &mainch_ctrl1);
	if (ret < 0) {
		dev_err(di->dev, "ab8500 read failed %d\n", __LINE__);
		return ret;
	}
	dev_dbg(di->dev, "AC charger ctrl: 0x%02x\n", mainch_ctrl1);

	if (!(mainch_ctrl1 & MAIN_CH_ENA)) {
		dev_info(di->dev, "Charging has been disabled abnormally and will be re-enabled\n");

		ret = abx500_mask_and_set_register_interruptible(di->dev,
					AB8500_CHARGER, AB8500_CHARGER_CTRL,
					DROP_COUNT_RESET, DROP_COUNT_RESET);

		if (ret < 0) {
			dev_err(di->dev, "ab8500 write failed %d\n", __LINE__);
			return ret;
		}

		ret = ab8500_charger_ac_en(&di->usb_chg, true, vset, iset);
		if (ret < 0) {
			dev_err(di->dev, "failed to enable AC charger %d\n",
				__LINE__);
			return ret;
		}
	}
	return ret;
}