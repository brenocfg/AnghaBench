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
struct img_i2s_in {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_sys; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int img_i2s_in_check_rate(struct img_i2s_in *i2s,
		unsigned int sample_rate, unsigned int frame_size,
		unsigned int *bclk_filter_enable,
		unsigned int *bclk_filter_value)
{
	unsigned int bclk_freq, cur_freq;

	bclk_freq = sample_rate * frame_size;

	cur_freq = clk_get_rate(i2s->clk_sys);

	if (cur_freq >= bclk_freq * 8) {
		*bclk_filter_enable = 1;
		*bclk_filter_value = 0;
	} else if (cur_freq >= bclk_freq * 7) {
		*bclk_filter_enable = 1;
		*bclk_filter_value = 1;
	} else if (cur_freq >= bclk_freq * 6) {
		*bclk_filter_enable = 0;
		*bclk_filter_value = 0;
	} else {
		dev_err(i2s->dev,
			"Sys clock rate %u insufficient for sample rate %u\n",
			cur_freq, sample_rate);
		return -EINVAL;
	}

	return 0;
}