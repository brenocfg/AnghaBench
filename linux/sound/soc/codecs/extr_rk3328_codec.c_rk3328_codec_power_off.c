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
struct rk3328_codec_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_ALL_MASK ; 
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_ALL_ON ; 
 int /*<<< orphan*/  DAC_CHARGE_DISCHARGE ; 
 int /*<<< orphan*/  DAC_CHARGE_XCHARGE_MASK ; 
 int /*<<< orphan*/  DAC_PRECHARGE_CTRL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3328_codec_power_off(struct rk3328_codec_priv *rk3328, int wait_ms)
{
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_XCHARGE_MASK, DAC_CHARGE_DISCHARGE);
	mdelay(10);
	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_ALL_ON);
	mdelay(wait_ms);

	return 0;
}