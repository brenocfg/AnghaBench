#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ltc294x_info {int id; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  LTC2942_ID 130 
 int LTC2942_REG_CONTROL_MODE_SCAN ; 
#define  LTC2943_ID 129 
 int LTC2943_REG_CONTROL_MODE_SCAN ; 
#define  LTC2944_ID 128 
 int /*<<< orphan*/  LTC294X_REG_CONTROL ; 
 int LTC294X_REG_CONTROL_ALCC_CONFIG_DISABLED ; 
 int LTC294X_REG_CONTROL_PRESCALER_SET (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ltc294x_read_regs (TYPE_1__*,int /*<<< orphan*/ ,int*,int) ; 
 int ltc294x_write_regs (TYPE_1__*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltc294x_reset(const struct ltc294x_info *info, int prescaler_exp)
{
	int ret;
	u8 value;
	u8 control;

	/* Read status and control registers */
	ret = ltc294x_read_regs(info->client, LTC294X_REG_CONTROL, &value, 1);
	if (ret < 0) {
		dev_err(&info->client->dev,
			"Could not read registers from device\n");
		goto error_exit;
	}

	control = LTC294X_REG_CONTROL_PRESCALER_SET(prescaler_exp) |
				LTC294X_REG_CONTROL_ALCC_CONFIG_DISABLED;
	/* Put device into "monitor" mode */
	switch (info->id) {
	case LTC2942_ID:	/* 2942 measures every 2 sec */
		control |= LTC2942_REG_CONTROL_MODE_SCAN;
		break;
	case LTC2943_ID:
	case LTC2944_ID:	/* 2943 and 2944 measure every 10 sec */
		control |= LTC2943_REG_CONTROL_MODE_SCAN;
		break;
	default:
		break;
	}

	if (value != control) {
		ret = ltc294x_write_regs(info->client,
			LTC294X_REG_CONTROL, &control, 1);
		if (ret < 0) {
			dev_err(&info->client->dev,
				"Could not write register\n");
			goto error_exit;
		}
	}

	return 0;

error_exit:
	return ret;
}