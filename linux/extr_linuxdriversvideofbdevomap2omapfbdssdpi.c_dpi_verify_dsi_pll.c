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
struct dss_pll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_pll_disable (struct dss_pll*) ; 
 int dss_pll_enable (struct dss_pll*) ; 

__attribute__((used)) static int dpi_verify_dsi_pll(struct dss_pll *pll)
{
	int r;

	/* do initial setup with the PLL to see if it is operational */

	r = dss_pll_enable(pll);
	if (r)
		return r;

	dss_pll_disable(pll);

	return 0;
}