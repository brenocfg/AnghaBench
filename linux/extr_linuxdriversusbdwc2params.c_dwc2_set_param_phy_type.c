#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int phy_type; } ;
struct TYPE_3__ {scalar_t__ hs_phy_type; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
 void* DWC2_PHY_TYPE_PARAM_FS ; 
 int DWC2_PHY_TYPE_PARAM_ULPI ; 
 int DWC2_PHY_TYPE_PARAM_UTMI ; 
 scalar_t__ GHWCFG2_HS_PHY_TYPE_NOT_SUPPORTED ; 
 scalar_t__ GHWCFG2_HS_PHY_TYPE_UTMI ; 
 scalar_t__ GHWCFG2_HS_PHY_TYPE_UTMI_ULPI ; 
 scalar_t__ dwc2_is_fs_iot (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_set_param_phy_type(struct dwc2_hsotg *hsotg)
{
	int val;
	u32 hs_phy_type = hsotg->hw_params.hs_phy_type;

	val = DWC2_PHY_TYPE_PARAM_FS;
	if (hs_phy_type != GHWCFG2_HS_PHY_TYPE_NOT_SUPPORTED) {
		if (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI ||
		    hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI)
			val = DWC2_PHY_TYPE_PARAM_UTMI;
		else
			val = DWC2_PHY_TYPE_PARAM_ULPI;
	}

	if (dwc2_is_fs_iot(hsotg))
		hsotg->params.phy_type = DWC2_PHY_TYPE_PARAM_FS;

	hsotg->params.phy_type = val;
}