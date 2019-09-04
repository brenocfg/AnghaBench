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
struct gxt4500_par {int refclk_ps; int pll_m; int pll_pd1; int pll_pd2; int pll_n; } ;

/* Variables and functions */

__attribute__((used)) static int calc_pixclock(struct gxt4500_par *par)
{
	return par->refclk_ps * par->pll_m * par->pll_pd1 * par->pll_pd2
		/ par->pll_n;
}