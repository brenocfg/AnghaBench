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
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 scalar_t__ mxc_ahb_clk ; 
 scalar_t__ mxc_ipg_clk ; 
 scalar_t__ mxc_per_clk ; 

void fsl_udc_clk_release(void)
{
	if (mxc_per_clk)
		clk_disable_unprepare(mxc_per_clk);
	clk_disable_unprepare(mxc_ahb_clk);
	clk_disable_unprepare(mxc_ipg_clk);
}