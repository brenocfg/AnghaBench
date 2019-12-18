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
struct hdspm {unsigned int system_sample_rate; } ;

/* Variables and functions */
 unsigned int hdspm_external_sample_rate (struct hdspm*) ; 
 unsigned int hdspm_get_pll_freq (struct hdspm*) ; 
 scalar_t__ hdspm_system_clock_mode (struct hdspm*) ; 

__attribute__((used)) static int hdspm_get_system_sample_rate(struct hdspm *hdspm)
{
	unsigned int rate;

	rate = hdspm_get_pll_freq(hdspm);

	if (rate > 207000) {
		/* Unreasonable high sample rate as seen on PCI MADI cards. */
		if (0 == hdspm_system_clock_mode(hdspm)) {
			/* master mode, return internal sample rate */
			rate = hdspm->system_sample_rate;
		} else {
			/* slave mode, return external sample rate */
			rate = hdspm_external_sample_rate(hdspm);
			if (!rate)
				rate = hdspm->system_sample_rate;
		}
	}

	return rate;
}