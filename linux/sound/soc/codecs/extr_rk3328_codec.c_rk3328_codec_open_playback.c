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
struct rk3328_codec_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  spk_depop_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  msk; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_ALL_MASK ; 
 int /*<<< orphan*/  DAC_CHARGE_CURRENT_I ; 
 int /*<<< orphan*/  DAC_PRECHARGE_CTRL ; 
 int /*<<< orphan*/  HPOUTL_GAIN_CTRL ; 
 int /*<<< orphan*/  HPOUTL_GAIN_MASK ; 
 int /*<<< orphan*/  HPOUTR_GAIN_CTRL ; 
 int /*<<< orphan*/  HPOUTR_GAIN_MASK ; 
 int /*<<< orphan*/  OUT_VOLUME ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 TYPE_1__* playback_open_list ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3328_analog_output (struct rk3328_codec_priv*,int) ; 

__attribute__((used)) static int rk3328_codec_open_playback(struct rk3328_codec_priv *rk3328)
{
	int i;

	regmap_update_bits(rk3328->regmap, DAC_PRECHARGE_CTRL,
			   DAC_CHARGE_CURRENT_ALL_MASK,
			   DAC_CHARGE_CURRENT_I);

	for (i = 0; i < ARRAY_SIZE(playback_open_list); i++) {
		regmap_update_bits(rk3328->regmap,
				   playback_open_list[i].reg,
				   playback_open_list[i].msk,
				   playback_open_list[i].val);
		mdelay(1);
	}

	msleep(rk3328->spk_depop_time);
	rk3328_analog_output(rk3328, 1);

	regmap_update_bits(rk3328->regmap, HPOUTL_GAIN_CTRL,
			   HPOUTL_GAIN_MASK, OUT_VOLUME);
	regmap_update_bits(rk3328->regmap, HPOUTR_GAIN_CTRL,
			   HPOUTR_GAIN_MASK, OUT_VOLUME);

	return 0;
}