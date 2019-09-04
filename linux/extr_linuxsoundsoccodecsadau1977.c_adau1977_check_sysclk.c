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

__attribute__((used)) static bool adau1977_check_sysclk(unsigned int mclk, unsigned int base_freq)
{
	unsigned int mcs;

	if (mclk % (base_freq * 128) != 0)
		return false;

	mcs = mclk / (128 * base_freq);
	if (mcs < 1 || mcs > 6 || mcs == 5)
		return false;

	return true;
}