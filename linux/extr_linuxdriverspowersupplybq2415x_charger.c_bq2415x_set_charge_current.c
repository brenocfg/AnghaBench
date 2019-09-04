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
struct TYPE_2__ {int resistor_sense; } ;
struct bq2415x_device {TYPE_1__ init_data; } ;

/* Variables and functions */
 int BQ2415X_MASK_RESET ; 
 int BQ2415X_MASK_VI_CHRG ; 
 int /*<<< orphan*/  BQ2415X_REG_CURRENT ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_VI_CHRG ; 
 int EINVAL ; 
 int bq2415x_i2c_write_mask (struct bq2415x_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_set_charge_current(struct bq2415x_device *bq, int mA)
{
	int val;

	if (bq->init_data.resistor_sense <= 0)
		return -EINVAL;

	val = (mA * bq->init_data.resistor_sense - 37400) / 6800;
	if (val < 0)
		val = 0;
	else if (val > 7)
		val = 7;

	return bq2415x_i2c_write_mask(bq, BQ2415X_REG_CURRENT, val,
			BQ2415X_MASK_VI_CHRG | BQ2415X_MASK_RESET,
			BQ2415X_SHIFT_VI_CHRG);
}