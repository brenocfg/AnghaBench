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
typedef  int /*<<< orphan*/  u8 ;
struct ltc294x_info {scalar_t__ Qlsb; int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I16_LSB (int) ; 
 int /*<<< orphan*/  I16_MSB (int) ; 
 int /*<<< orphan*/  LTC294X_REG_ACC_CHARGE_MSB ; 
 int /*<<< orphan*/  LTC294X_REG_CONTROL ; 
 int /*<<< orphan*/  LTC294X_REG_CONTROL_SHUTDOWN_MASK ; 
 int convert_uAh_to_bin (struct ltc294x_info const*,int) ; 
 int ltc294x_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ltc294x_write_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ltc294x_set_charge_now(const struct ltc294x_info *info, int val)
{
	int ret;
	u8 dataw[2];
	u8 ctrl_reg;
	s32 value;

	value = convert_uAh_to_bin(info, val);
	/* Direction depends on how sense+/- were connected */
	if (info->Qlsb < 0)
		value += 0xFFFF;
	if ((value < 0) || (value > 0xFFFF)) /* input validation */
		return -EINVAL;

	/* Read control register */
	ret = ltc294x_read_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);
	if (ret < 0)
		return ret;
	/* Disable analog section */
	ctrl_reg |= LTC294X_REG_CONTROL_SHUTDOWN_MASK;
	ret = ltc294x_write_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);
	if (ret < 0)
		return ret;
	/* Set new charge value */
	dataw[0] = I16_MSB(value);
	dataw[1] = I16_LSB(value);
	ret = ltc294x_write_regs(info->client,
		LTC294X_REG_ACC_CHARGE_MSB, &dataw[0], 2);
	if (ret < 0)
		goto error_exit;
	/* Enable analog section */
error_exit:
	ctrl_reg &= ~LTC294X_REG_CONTROL_SHUTDOWN_MASK;
	ret = ltc294x_write_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);

	return ret < 0 ? ret : 0;
}