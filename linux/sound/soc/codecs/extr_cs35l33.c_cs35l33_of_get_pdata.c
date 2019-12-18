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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct cs35l33_pdata {int boost_ctl; int amp_drv_sel; int ramp_rate; int boost_ipk; int imon_adc_scale; } ;
struct cs35l33_private {int enable_soft_ramp; struct cs35l33_pdata pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs35l33_get_hg_data (struct device_node*,struct cs35l33_pdata*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int cs35l33_of_get_pdata(struct device *dev,
				struct cs35l33_private *cs35l33)
{
	struct device_node *np = dev->of_node;
	struct cs35l33_pdata *pdata = &cs35l33->pdata;
	u32 val32;

	if (!np)
		return 0;

	if (of_property_read_u32(np, "cirrus,boost-ctl", &val32) >= 0) {
		pdata->boost_ctl = val32;
		pdata->amp_drv_sel = 1;
	}

	if (of_property_read_u32(np, "cirrus,ramp-rate", &val32) >= 0) {
		pdata->ramp_rate = val32;
		cs35l33->enable_soft_ramp = true;
	}

	if (of_property_read_u32(np, "cirrus,boost-ipk", &val32) >= 0)
		pdata->boost_ipk = val32;

	if (of_property_read_u32(np, "cirrus,imon-adc-scale", &val32) >= 0) {
		if ((val32 == 0x0) || (val32 == 0x7) || (val32 == 0x6))
			pdata->imon_adc_scale = val32;
		else
			/* use default value */
			pdata->imon_adc_scale = 0x8;
	} else {
		/* use default value */
		pdata->imon_adc_scale = 0x8;
	}

	cs35l33_get_hg_data(np, pdata);

	return 0;
}