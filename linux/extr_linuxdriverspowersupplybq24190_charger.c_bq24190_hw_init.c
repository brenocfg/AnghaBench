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
struct bq24190_dev_info {int /*<<< orphan*/  ss_reg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_SS ; 
 int /*<<< orphan*/  BQ24190_REG_VPRS ; 
 scalar_t__ BQ24190_REG_VPRS_PN_24190 ; 
 scalar_t__ BQ24190_REG_VPRS_PN_24192I ; 
 int /*<<< orphan*/  BQ24190_REG_VPRS_PN_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_VPRS_PN_SHIFT ; 
 int ENODEV ; 
 int bq24190_read (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bq24190_read_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bq24190_register_reset (struct bq24190_dev_info*) ; 
 int bq24190_set_config (struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int bq24190_hw_init(struct bq24190_dev_info *bdi)
{
	u8 v;
	int ret;

	/* First check that the device really is what its supposed to be */
	ret = bq24190_read_mask(bdi, BQ24190_REG_VPRS,
			BQ24190_REG_VPRS_PN_MASK,
			BQ24190_REG_VPRS_PN_SHIFT,
			&v);
	if (ret < 0)
		return ret;

	if (v != BQ24190_REG_VPRS_PN_24190 &&
	    v != BQ24190_REG_VPRS_PN_24192I) {
		dev_err(bdi->dev, "Error unknown model: 0x%02x\n", v);
		return -ENODEV;
	}

	ret = bq24190_register_reset(bdi);
	if (ret < 0)
		return ret;

	ret = bq24190_set_config(bdi);
	if (ret < 0)
		return ret;

	return bq24190_read(bdi, BQ24190_REG_SS, &bdi->ss_reg);
}