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
typedef  scalar_t__ u8 ;
struct ltc294x_info {scalar_t__ id; int /*<<< orphan*/  client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ LTC2941_ID ; 
 int /*<<< orphan*/  LTC294X_REG_CONTROL ; 
 scalar_t__ LTC294X_REG_CONTROL_ADC_DISABLE (scalar_t__) ; 
 struct ltc294x_info* i2c_get_clientdata (struct i2c_client*) ; 
 int ltc294x_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  ltc294x_write_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void ltc294x_i2c_shutdown(struct i2c_client *client)
{
	struct ltc294x_info *info = i2c_get_clientdata(client);
	int ret;
	u8 value;
	u8 control;

	/* The LTC2941 does not need any special handling */
	if (info->id == LTC2941_ID)
		return;

	/* Read control register */
	ret = ltc294x_read_regs(info->client, LTC294X_REG_CONTROL, &value, 1);
	if (ret < 0)
		return;

	/* Disable continuous ADC conversion as this drains the battery */
	control = LTC294X_REG_CONTROL_ADC_DISABLE(value);
	if (control != value)
		ltc294x_write_regs(info->client, LTC294X_REG_CONTROL,
			&control, 1);
}