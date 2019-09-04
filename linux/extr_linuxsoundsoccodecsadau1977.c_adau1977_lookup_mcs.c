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
struct adau1977 {unsigned int sysclk; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int adau1977_lookup_mcs(struct adau1977 *adau1977, unsigned int rate,
	unsigned int fs)
{
	unsigned int mcs;

	/*
	 * rate = sysclk / (512 * mcs_lut[mcs]) * 2**fs
	 * => mcs_lut[mcs] = sysclk / (512 * rate) * 2**fs
	 * => mcs_lut[mcs] = sysclk / ((512 / 2**fs) * rate)
	 */

	rate *= 512 >> fs;

	if (adau1977->sysclk % rate != 0)
		return -EINVAL;

	mcs = adau1977->sysclk / rate;

	/* The factors configured by MCS are 1, 2, 3, 4, 6 */
	if (mcs < 1 || mcs > 6 || mcs == 5)
		return -EINVAL;

	mcs = mcs - 1;
	if (mcs == 5)
		mcs = 4;

	return mcs;
}