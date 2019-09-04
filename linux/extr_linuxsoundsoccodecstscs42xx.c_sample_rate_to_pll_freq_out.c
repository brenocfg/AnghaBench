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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sample_rate_to_pll_freq_out(int sample_rate)
{
	switch (sample_rate) {
	case 11025:
	case 22050:
	case 44100:
	case 88200:
		return 112896000;
	case 8000:
	case 16000:
	case 32000:
	case 48000:
	case 96000:
		return 122880000;
	default:
		return -EINVAL;
	}
}