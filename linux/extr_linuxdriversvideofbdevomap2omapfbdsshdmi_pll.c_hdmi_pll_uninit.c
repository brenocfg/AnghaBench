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
struct hdmi_pll_data {struct dss_pll pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_pll_unregister (struct dss_pll*) ; 

void hdmi_pll_uninit(struct hdmi_pll_data *hpll)
{
	struct dss_pll *pll = &hpll->pll;

	dss_pll_unregister(pll);
}