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
struct img_spdif_in {int /*<<< orphan*/  clk_sys; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_spdif_in_check_max_rate(struct img_spdif_in *spdif,
		unsigned int sample_rate, unsigned long *actual_freq)
{
	unsigned long min_freq, freq_t;

	/* Clock rate must be at least 24x the bit rate */
	min_freq = sample_rate * 2 * 32 * 24;

	freq_t = clk_get_rate(spdif->clk_sys);

	if (freq_t < min_freq)
		return -EINVAL;

	*actual_freq = freq_t;

	return 0;
}