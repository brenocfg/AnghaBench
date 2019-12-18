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

__attribute__((used)) static bool is_pll_freq_available(unsigned int source, unsigned int target)
{
	unsigned int Ndiv;

	if (source == 0 || target == 0)
		return false;

	/* Scale up target to PLL operating frequency */
	target *= 4;
	Ndiv = target / source;

	if (Ndiv < 6) {
		source >>= 1;
		Ndiv = target / source;
	}

	if ((Ndiv < 6) || (Ndiv > 12))
		return false;

	return true;
}