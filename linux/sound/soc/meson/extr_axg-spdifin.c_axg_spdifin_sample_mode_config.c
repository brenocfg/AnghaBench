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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct axg_spdifin {int /*<<< orphan*/  map; int /*<<< orphan*/  refclk; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SPDIFIN_CTRL0 ; 
 int /*<<< orphan*/  SPDIFIN_CTRL0_WIDTH_SEL ; 
 int /*<<< orphan*/  SPDIFIN_CTRL1 ; 
 int /*<<< orphan*/  SPDIFIN_CTRL1_BASE_TIMER ; 
 int SPDIFIN_MODE_NUM ; 
 unsigned int axg_spdifin_mode_timer (struct axg_spdifin*,int,unsigned int) ; 
 int /*<<< orphan*/  axg_spdifin_write_threshold (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  axg_spdifin_write_timer (int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_spdifin_sample_mode_config(struct snd_soc_dai *dai,
					  struct axg_spdifin *priv)
{
	unsigned int rate, t_next;
	int ret, i = SPDIFIN_MODE_NUM - 1;

	/* Set spdif input reference clock */
	ret = clk_set_rate(priv->refclk, priv->conf->ref_rate);
	if (ret) {
		dev_err(dai->dev, "reference clock rate set failed\n");
		return ret;
	}

	/*
	 * The rate actually set might be slightly different, get
	 * the actual rate for the following mode calculation
	 */
	rate = clk_get_rate(priv->refclk);

	/* HW will update mode every 1ms */
	regmap_update_bits(priv->map, SPDIFIN_CTRL1,
			   SPDIFIN_CTRL1_BASE_TIMER,
			   FIELD_PREP(SPDIFIN_CTRL1_BASE_TIMER, rate / 1000));

	/* Threshold based on the minimum width between two edges */
	regmap_update_bits(priv->map, SPDIFIN_CTRL0,
			   SPDIFIN_CTRL0_WIDTH_SEL, SPDIFIN_CTRL0_WIDTH_SEL);

	/* Calculate the last timer which has no threshold */
	t_next = axg_spdifin_mode_timer(priv, i, rate);
	axg_spdifin_write_timer(priv->map, i, t_next);

	do {
		unsigned int t;

		i -= 1;

		/* Calculate the timer */
		t = axg_spdifin_mode_timer(priv, i, rate);

		/* Set the timer value */
		axg_spdifin_write_timer(priv->map, i, t);

		/* Set the threshold value */
		axg_spdifin_write_threshold(priv->map, i, t + t_next);

		/* Save the current timer for the next threshold calculation */
		t_next = t;

	} while (i > 0);

	return 0;
}