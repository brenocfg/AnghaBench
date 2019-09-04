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

__attribute__((used)) static unsigned int spi_imx_clkdiv_2(unsigned int fin,
		unsigned int fspi, unsigned int *fres)
{
	int i, div = 4;

	for (i = 0; i < 7; i++) {
		if (fspi * div >= fin)
			goto out;
		div <<= 1;
	}

out:
	*fres = fin / div;
	return i;
}