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
struct atmel_i2s_gck_param {scalar_t__ fs; } ;
struct atmel_i2s_dev {struct atmel_i2s_gck_param const* gck_param; int /*<<< orphan*/  dev; int /*<<< orphan*/  gclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct atmel_i2s_gck_param*) ; 
 int EINVAL ; 
 int INT_MAX ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct atmel_i2s_gck_param* gck_params ; 

__attribute__((used)) static int atmel_i2s_get_gck_param(struct atmel_i2s_dev *dev, int fs)
{
	int i, best;

	if (!dev->gclk) {
		dev_err(dev->dev, "cannot generate the I2S Master Clock\n");
		return -EINVAL;
	}

	/*
	 * Find the best possible settings to generate the I2S Master Clock
	 * from the PLL Audio.
	 */
	dev->gck_param = NULL;
	best = INT_MAX;
	for (i = 0; i < ARRAY_SIZE(gck_params); ++i) {
		const struct atmel_i2s_gck_param *gck_param = &gck_params[i];
		int val = abs(fs - gck_param->fs);

		if (val < best) {
			best = val;
			dev->gck_param = gck_param;
		}
	}

	return 0;
}