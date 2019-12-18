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
struct wcd9335_codec {int master_bias_users; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_ANA_BIAS ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_CTL_MODE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_DISABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_EN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wcd9335_enable_master_bias(struct wcd9335_codec *wcd)
{
	wcd->master_bias_users++;
	if (wcd->master_bias_users == 1) {
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_EN_MASK,
					WCD9335_ANA_BIAS_ENABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_PRECHRG_EN_MASK,
					WCD9335_ANA_BIAS_PRECHRG_ENABLE);
		/*
		 * 1ms delay is required after pre-charge is enabled
		 * as per HW requirement
		 */
		usleep_range(1000, 1100);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
					WCD9335_ANA_BIAS_PRECHRG_EN_MASK,
					WCD9335_ANA_BIAS_PRECHRG_DISABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL);
	}

	return 0;
}