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
struct rk3328_codec_priv {int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  msk; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_ALL_MASK ; 
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_ALL_ON ; 
 int /*<<< orphan*/  DAC_PRECHARGE_CTRL ; 
 int /*<<< orphan*/  HPOUTL_GAIN_CTRL ; 
 int /*<<< orphan*/  HPOUTL_GAIN_MASK ; 
 int /*<<< orphan*/  HPOUTR_GAIN_CTRL ; 
 int /*<<< orphan*/  HPOUTR_GAIN_MASK ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* playback_close_list ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3328_analog_output (struct rk3328_codec_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3328_codec_reset (struct rk3328_codec_priv*) ; 

__attribute__((used)) static int rk3328_codec_close_playback(struct rk3328_codec_priv *rk3328)
{
	size_t i;

	rk3328_analog_output(rk3328, 0);

	regmap_update_bits(rk3328->regmap, HPOUTL_GAIN_CTRL,
			   HPOUTL_GAIN_MASK, 0);
	regmap_update_bits(rk3328->regmap, HPOUTR_GAIN_CTRL,
			   HPOUTR_GAIN_MASK, 0);

	for (i = 0; i < ARRAY_SIZE(playback_close_list); i++) {
		regmap_update_bits(rk3328->regmap,
				   playback_close_list[i].reg,
				   playback_close_list[i].msk,
				   playback_close_list[i].val);
		mdelay(1);
	}

	/* Workaround for silence when changed Fs 48 -> 44.1kHz */
	rk3328_codec_reset(rk3328);

	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_ALL_ON);

	return 0;
}