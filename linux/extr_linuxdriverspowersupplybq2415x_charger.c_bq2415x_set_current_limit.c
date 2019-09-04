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
struct bq2415x_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_MASK_LIMIT ; 
 int /*<<< orphan*/  BQ2415X_REG_CONTROL ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_LIMIT ; 
 int bq2415x_i2c_write_mask (struct bq2415x_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_set_current_limit(struct bq2415x_device *bq, int mA)
{
	int val;

	if (mA <= 100)
		val = 0;
	else if (mA <= 500)
		val = 1;
	else if (mA <= 800)
		val = 2;
	else
		val = 3;

	return bq2415x_i2c_write_mask(bq, BQ2415X_REG_CONTROL, val,
			BQ2415X_MASK_LIMIT, BQ2415X_SHIFT_LIMIT);
}