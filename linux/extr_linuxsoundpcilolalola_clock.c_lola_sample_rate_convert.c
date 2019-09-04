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

unsigned int lola_sample_rate_convert(unsigned int coded)
{
	unsigned int freq;

	/* base frequency */
	switch (coded & 0x3) {
	case 0:     freq = 48000; break;
	case 1:     freq = 44100; break;
	case 2:     freq = 32000; break;
	default:    return 0;   /* error */
	}

	/* multiplier / devisor */
	switch (coded & 0x1c) {
	case (0 << 2):    break;
	case (4 << 2):    break;
	case (1 << 2):    freq *= 2; break;
	case (2 << 2):    freq *= 4; break;
	case (5 << 2):    freq /= 2; break;
	case (6 << 2):    freq /= 4; break;
	default:        return 0;   /* error */
	}

	/* ajustement */
	switch (coded & 0x60) {
	case (0 << 5):    break;
	case (1 << 5):    freq = (freq * 999) / 1000; break;
	case (2 << 5):    freq = (freq * 1001) / 1000; break;
	default:        return 0;   /* error */
	}
	return freq;
}