#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_at73c213 {unsigned long bitrate; TYPE_3__* spi; TYPE_2__* ssc; TYPE_1__* board; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; } ;
struct TYPE_4__ {int /*<<< orphan*/  dac_clk; } ;

/* Variables and functions */
 int BITRATE_MAX ; 
 int BITRATE_MIN ; 
 int BITRATE_TARGET ; 
 int /*<<< orphan*/  CMR ; 
 int ENXIO ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int snd_at73c213_set_bitrate(struct snd_at73c213 *chip)
{
	unsigned long ssc_rate = clk_get_rate(chip->ssc->clk);
	unsigned long dac_rate_new, ssc_div;
	int status;
	unsigned long ssc_div_max, ssc_div_min;
	int max_tries;

	/*
	 * We connect two clocks here, picking divisors so the I2S clocks
	 * out data at the same rate the DAC clocks it in ... and as close
	 * as practical to the desired target rate.
	 *
	 * The DAC master clock (MCLK) is programmable, and is either 256
	 * or (not here) 384 times the I2S output clock (BCLK).
	 */

	/* SSC clock / (bitrate * stereo * 16-bit). */
	ssc_div = ssc_rate / (BITRATE_TARGET * 2 * 16);
	ssc_div_min = ssc_rate / (BITRATE_MAX * 2 * 16);
	ssc_div_max = ssc_rate / (BITRATE_MIN * 2 * 16);
	max_tries = (ssc_div_max - ssc_div_min) / 2;

	if (max_tries < 1)
		max_tries = 1;

	/* ssc_div must be even. */
	ssc_div = (ssc_div + 1) & ~1UL;

	if ((ssc_rate / (ssc_div * 2 * 16)) < BITRATE_MIN) {
		ssc_div -= 2;
		if ((ssc_rate / (ssc_div * 2 * 16)) > BITRATE_MAX)
			return -ENXIO;
	}

	/* Search for a possible bitrate. */
	do {
		/* SSC clock / (ssc divider * 16-bit * stereo). */
		if ((ssc_rate / (ssc_div * 2 * 16)) < BITRATE_MIN)
			return -ENXIO;

		/* 256 / (2 * 16) = 8 */
		dac_rate_new = 8 * (ssc_rate / ssc_div);

		status = clk_round_rate(chip->board->dac_clk, dac_rate_new);
		if (status <= 0)
			return status;

		/* Ignore difference smaller than 256 Hz. */
		if ((status/256) == (dac_rate_new/256))
			goto set_rate;

		ssc_div += 2;
	} while (--max_tries);

	/* Not able to find a valid bitrate. */
	return -ENXIO;

set_rate:
	status = clk_set_rate(chip->board->dac_clk, status);
	if (status < 0)
		return status;

	/* Set divider in SSC device. */
	ssc_writel(chip->ssc->regs, CMR, ssc_div/2);

	/* SSC clock / (ssc divider * 16-bit * stereo). */
	chip->bitrate = ssc_rate / (ssc_div * 16 * 2);

	dev_info(&chip->spi->dev,
			"at73c213: supported bitrate is %lu (%lu divider)\n",
			chip->bitrate, ssc_div);

	return 0;
}