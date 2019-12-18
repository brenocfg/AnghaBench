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
typedef  int u8 ;
typedef  int u16 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct clk_bulk_data {char* id; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int AIC32X4_MAX_CODEC_CLKIN_FREQ ; 
 unsigned int AIC32X4_MAX_DOSR_FREQ ; 
 unsigned int AIC32X4_MIN_DOSR_FREQ ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct clk_bulk_data*) ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  aic32x4_set_aosr (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  aic32x4_set_dosr (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  aic32x4_set_processing_blocks (struct snd_soc_component*,int,int) ; 
 scalar_t__ clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_clk_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_bulk_data*) ; 

__attribute__((used)) static int aic32x4_setup_clocks(struct snd_soc_component *component,
				unsigned int sample_rate)
{
	u8 aosr;
	u16 dosr;
	u8 adc_resource_class, dac_resource_class;
	u8 madc, nadc, mdac, ndac, max_nadc, min_mdac, max_ndac;
	u8 dosr_increment;
	u16 max_dosr, min_dosr;
	unsigned long adc_clock_rate, dac_clock_rate;
	int ret;

	struct clk_bulk_data clocks[] = {
		{ .id = "pll" },
		{ .id = "nadc" },
		{ .id = "madc" },
		{ .id = "ndac" },
		{ .id = "mdac" },
		{ .id = "bdiv" },
	};
	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(clocks), clocks);
	if (ret)
		return ret;

	if (sample_rate <= 48000) {
		aosr = 128;
		adc_resource_class = 6;
		dac_resource_class = 8;
		dosr_increment = 8;
		aic32x4_set_processing_blocks(component, 1, 1);
	} else if (sample_rate <= 96000) {
		aosr = 64;
		adc_resource_class = 6;
		dac_resource_class = 8;
		dosr_increment = 4;
		aic32x4_set_processing_blocks(component, 1, 9);
	} else if (sample_rate == 192000) {
		aosr = 32;
		adc_resource_class = 3;
		dac_resource_class = 4;
		dosr_increment = 2;
		aic32x4_set_processing_blocks(component, 13, 19);
	} else {
		dev_err(component->dev, "Sampling rate not supported\n");
		return -EINVAL;
	}

	madc = DIV_ROUND_UP((32 * adc_resource_class), aosr);
	max_dosr = (AIC32X4_MAX_DOSR_FREQ / sample_rate / dosr_increment) *
			dosr_increment;
	min_dosr = (AIC32X4_MIN_DOSR_FREQ / sample_rate / dosr_increment) *
			dosr_increment;
	max_nadc = AIC32X4_MAX_CODEC_CLKIN_FREQ / (madc * aosr * sample_rate);

	for (nadc = max_nadc; nadc > 0; --nadc) {
		adc_clock_rate = nadc * madc * aosr * sample_rate;
		for (dosr = max_dosr; dosr >= min_dosr;
				dosr -= dosr_increment) {
			min_mdac = DIV_ROUND_UP((32 * dac_resource_class), dosr);
			max_ndac = AIC32X4_MAX_CODEC_CLKIN_FREQ /
					(min_mdac * dosr * sample_rate);
			for (mdac = min_mdac; mdac <= 128; ++mdac) {
				for (ndac = max_ndac; ndac > 0; --ndac) {
					dac_clock_rate = ndac * mdac * dosr *
							sample_rate;
					if (dac_clock_rate == adc_clock_rate) {
						if (clk_round_rate(clocks[0].clk, dac_clock_rate) == 0)
							continue;

						clk_set_rate(clocks[0].clk,
							dac_clock_rate);

						clk_set_rate(clocks[1].clk,
							sample_rate * aosr *
							madc);
						clk_set_rate(clocks[2].clk,
							sample_rate * aosr);
						aic32x4_set_aosr(component,
							aosr);

						clk_set_rate(clocks[3].clk,
							sample_rate * dosr *
							mdac);
						clk_set_rate(clocks[4].clk,
							sample_rate * dosr);
						aic32x4_set_dosr(component,
							dosr);

						clk_set_rate(clocks[5].clk,
							sample_rate * 32);
						return 0;
					}
				}
			}
		}
	}

	dev_err(component->dev,
		"Could not set clocks to support sample rate.\n");
	return -EINVAL;
}