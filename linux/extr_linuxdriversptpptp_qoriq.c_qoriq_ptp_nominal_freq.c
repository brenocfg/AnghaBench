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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 qoriq_ptp_nominal_freq(u32 clk_src)
{
	u32 remainder = 0;

	clk_src /= 1000000;
	remainder = clk_src % 100;
	if (remainder) {
		clk_src -= remainder;
		clk_src += 100;
	}

	do {
		clk_src -= 100;

	} while (1000 % clk_src);

	return clk_src * 1000000;
}