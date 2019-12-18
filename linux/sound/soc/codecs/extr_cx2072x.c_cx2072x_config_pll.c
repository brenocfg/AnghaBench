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
typedef  int u64 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct cx2072x_priv {unsigned int sample_rate; unsigned int mclk_rate; int /*<<< orphan*/  regmap; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_ANALOG_TEST4 ; 
 int /*<<< orphan*/  CX2072X_ANALOG_TEST6 ; 
 int /*<<< orphan*/  CX2072X_ANALOG_TEST7 ; 
 int /*<<< orphan*/  CX2072X_ANALOG_TEST8 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST16 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST17 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST18 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST19 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST20 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 unsigned int get_div_from_mclk (unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx2072x_config_pll(struct cx2072x_priv *cx2072x)
{
	struct device *dev = cx2072x->dev;
	unsigned int pre_div;
	unsigned int pre_div_val;
	unsigned int pll_input;
	unsigned int pll_output;
	unsigned int int_div;
	unsigned int frac_div;
	u64 frac_num;
	unsigned int frac;
	unsigned int sample_rate = cx2072x->sample_rate;
	int pt_sample_per_sync = 2;
	int pt_clock_per_sample = 96;

	switch (sample_rate) {
	case 48000:
	case 32000:
	case 24000:
	case 16000:
		break;

	case 96000:
		pt_sample_per_sync = 1;
		pt_clock_per_sample = 48;
		break;

	case 192000:
		pt_sample_per_sync = 0;
		pt_clock_per_sample = 24;
		break;

	default:
		dev_err(dev, "Unsupported sample rate %d\n", sample_rate);
		return -EINVAL;
	}

	/* Configure PLL settings */
	pre_div = get_div_from_mclk(cx2072x->mclk_rate);
	pll_input = cx2072x->mclk_rate / pre_div;
	pll_output = sample_rate * 3072;
	int_div = pll_output / pll_input;
	frac_div = pll_output - (int_div * pll_input);

	if (frac_div) {
		frac_div *= 1000;
		frac_div /= pll_input;
		frac_num = (u64)(4000 + frac_div) * ((1 << 20) - 4);
		do_div(frac_num, 7);
		frac = ((u32)frac_num + 499) / 1000;
	}
	pre_div_val = (pre_div - 1) * 2;

	regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST4,
		     0x40 | (pre_div_val << 8));
	if (frac_div == 0) {
		/* Int mode */
		regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST7, 0x100);
	} else {
		/* frac mode */
		regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST6,
			     frac & 0xfff);
		regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST7,
			     (u8)(frac >> 12));
	}

	int_div--;
	regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST8, int_div);

	/* configure PLL tracking */
	if (frac_div == 0) {
		/* disable PLL tracking */
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST16, 0x00);
	} else {
		/* configure and enable PLL tracking */
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST16,
			     (pt_sample_per_sync << 4) & 0xf0);
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST17,
			     pt_clock_per_sample);
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST18,
			     pt_clock_per_sample * 3 / 2);
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST19, 0x01);
		regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST20, 0x02);
		regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_TEST16,
				   0x01, 0x01);
	}

	return 0;
}