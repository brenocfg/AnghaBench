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
struct dss_pll_clock_info {int dummy; } ;
struct dss_pll {struct dss_pll_clock_info cinfo; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_config ) (struct dss_pll*,struct dss_pll_clock_info const*) ;} ;

/* Variables and functions */
 int stub1 (struct dss_pll*,struct dss_pll_clock_info const*) ; 

int dss_pll_set_config(struct dss_pll *pll, const struct dss_pll_clock_info *cinfo)
{
	int r;

	r = pll->ops->set_config(pll, cinfo);
	if (r)
		return r;

	pll->cinfo = *cinfo;

	return 0;
}