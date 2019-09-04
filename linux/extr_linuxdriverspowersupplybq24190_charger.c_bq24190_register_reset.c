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
struct bq24190_dev_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_POC ; 
 int /*<<< orphan*/  BQ24190_REG_POC_RESET_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_POC_RESET_SHIFT ; 
 int EIO ; 
 int bq24190_read_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bq24190_write_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bq24190_register_reset(struct bq24190_dev_info *bdi)
{
	int ret, limit = 100;
	u8 v;

	/*
	 * This prop. can be passed on device instantiation from platform code:
	 * struct property_entry pe[] =
	 *   { PROPERTY_ENTRY_BOOL("disable-reset"), ... };
	 * struct i2c_board_info bi =
	 *   { .type = "bq24190", .addr = 0x6b, .properties = pe, .irq = irq };
	 * struct i2c_adapter ad = { ... };
	 * i2c_add_adapter(&ad);
	 * i2c_new_device(&ad, &bi);
	 */
	if (device_property_read_bool(bdi->dev, "disable-reset"))
		return 0;

	/* Reset the registers */
	ret = bq24190_write_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_RESET_MASK,
			BQ24190_REG_POC_RESET_SHIFT,
			0x1);
	if (ret < 0)
		return ret;

	/* Reset bit will be cleared by hardware so poll until it is */
	do {
		ret = bq24190_read_mask(bdi, BQ24190_REG_POC,
				BQ24190_REG_POC_RESET_MASK,
				BQ24190_REG_POC_RESET_SHIFT,
				&v);
		if (ret < 0)
			return ret;

		if (v == 0)
			return 0;

		usleep_range(100, 200);
	} while (--limit);

	return -EIO;
}