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
typedef  int u8 ;
struct ab8500_charger {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int AB8500_SW_CONTROL_FALLBACK ; 
 int AB8500_SYS_CTRL1_BLOCK ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int,int,int*) ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_ab8500 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_enable_disable_sw_fallback(struct ab8500_charger *di,
		bool fallback)
{
	u8 val;
	u8 reg;
	u8 bank;
	u8 bit;
	int ret;

	dev_dbg(di->dev, "SW Fallback: %d\n", fallback);

	if (is_ab8500(di->parent)) {
		bank = 0x15;
		reg = 0x0;
		bit = 3;
	} else {
		bank = AB8500_SYS_CTRL1_BLOCK;
		reg = AB8500_SW_CONTROL_FALLBACK;
		bit = 0;
	}

	/* read the register containing fallback bit */
	ret = abx500_get_register_interruptible(di->dev, bank, reg, &val);
	if (ret < 0) {
		dev_err(di->dev, "%d read failed\n", __LINE__);
		return;
	}

	if (is_ab8500(di->parent)) {
		/* enable the OPT emulation registers */
		ret = abx500_set_register_interruptible(di->dev, 0x11, 0x00, 0x2);
		if (ret) {
			dev_err(di->dev, "%d write failed\n", __LINE__);
			goto disable_otp;
		}
	}

	if (fallback)
		val |= (1 << bit);
	else
		val &= ~(1 << bit);

	/* write back the changed fallback bit value to register */
	ret = abx500_set_register_interruptible(di->dev, bank, reg, val);
	if (ret) {
		dev_err(di->dev, "%d write failed\n", __LINE__);
	}

disable_otp:
	if (is_ab8500(di->parent)) {
		/* disable the set OTP registers again */
		ret = abx500_set_register_interruptible(di->dev, 0x11, 0x00, 0x0);
		if (ret) {
			dev_err(di->dev, "%d write failed\n", __LINE__);
		}
	}
}