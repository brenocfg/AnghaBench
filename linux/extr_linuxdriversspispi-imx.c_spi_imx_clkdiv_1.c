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
 unsigned int* mxc_clkdivs ; 

__attribute__((used)) static unsigned int spi_imx_clkdiv_1(unsigned int fin,
		unsigned int fspi, unsigned int max, unsigned int *fres)
{
	int i;

	for (i = 2; i < max; i++)
		if (fspi * mxc_clkdivs[i] >= fin)
			break;

	*fres = fin / mxc_clkdivs[i];
	return i;
}