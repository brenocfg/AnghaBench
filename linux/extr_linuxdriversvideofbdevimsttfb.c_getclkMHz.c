#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pclk_m; int pclk_n; int pclk_p; } ;
struct imstt_par {TYPE_1__ init; } ;
typedef  int __u32 ;

/* Variables and functions */

__attribute__((used)) static __u32
getclkMHz(struct imstt_par *par)
{
	__u32 clk_m, clk_n, clk_p;

	clk_m = par->init.pclk_m;
	clk_n = par->init.pclk_n;
	clk_p = par->init.pclk_p;

	return 20 * (clk_m + 1) / ((clk_n + 1) * (clk_p ? 2 * clk_p : 1));
}