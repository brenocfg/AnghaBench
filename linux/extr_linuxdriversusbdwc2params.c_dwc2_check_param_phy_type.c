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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int phy_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  fs_phy_type; int /*<<< orphan*/  hs_phy_type; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
#define  DWC2_PHY_TYPE_PARAM_FS 130 
#define  DWC2_PHY_TYPE_PARAM_ULPI 129 
#define  DWC2_PHY_TYPE_PARAM_UTMI 128 
 int /*<<< orphan*/  GHWCFG2_FS_PHY_TYPE_DEDICATED ; 
 int /*<<< orphan*/  GHWCFG2_HS_PHY_TYPE_UTMI ; 
 int /*<<< orphan*/  GHWCFG2_HS_PHY_TYPE_UTMI_ULPI ; 
 int /*<<< orphan*/  dwc2_set_param_phy_type (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_check_param_phy_type(struct dwc2_hsotg *hsotg)
{
	int valid = 0;
	u32 hs_phy_type;
	u32 fs_phy_type;

	hs_phy_type = hsotg->hw_params.hs_phy_type;
	fs_phy_type = hsotg->hw_params.fs_phy_type;

	switch (hsotg->params.phy_type) {
	case DWC2_PHY_TYPE_PARAM_FS:
		if (fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED)
			valid = 1;
		break;
	case DWC2_PHY_TYPE_PARAM_UTMI:
		if ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI))
			valid = 1;
		break;
	case DWC2_PHY_TYPE_PARAM_ULPI:
		if ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI))
			valid = 1;
		break;
	default:
		break;
	}

	if (!valid)
		dwc2_set_param_phy_type(hsotg);
}