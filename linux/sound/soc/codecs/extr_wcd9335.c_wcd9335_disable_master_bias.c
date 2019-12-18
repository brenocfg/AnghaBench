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
struct wcd9335_codec {scalar_t__ master_bias_users; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_DISABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_CTL_MODE ; 
 int /*<<< orphan*/  WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcd9335_disable_master_bias(struct wcd9335_codec *wcd)
{
	if (wcd->master_bias_users <= 0)
		return -EINVAL;

	wcd->master_bias_users--;
	if (wcd->master_bias_users == 0) {
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_EN_MASK,
				WCD9335_ANA_BIAS_DISABLE);
		regmap_update_bits(wcd->regmap, WCD9335_ANA_BIAS,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE,
				WCD9335_ANA_BIAS_PRECHRG_CTL_MODE_MANUAL);
	}
	return 0;
}