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
struct TYPE_4__ {int utmi_phy_data_width; } ;
struct TYPE_3__ {int phy_utmi_width; } ;
struct dwc2_hsotg {TYPE_2__ hw_params; TYPE_1__ params; } ;

/* Variables and functions */
#define  GHWCFG4_UTMI_PHY_DATA_WIDTH_16 130 
#define  GHWCFG4_UTMI_PHY_DATA_WIDTH_8 129 
#define  GHWCFG4_UTMI_PHY_DATA_WIDTH_8_OR_16 128 
 int /*<<< orphan*/  dwc2_set_param_phy_utmi_width (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_check_param_phy_utmi_width(struct dwc2_hsotg *hsotg)
{
	int valid = 0;
	int param = hsotg->params.phy_utmi_width;
	int width = hsotg->hw_params.utmi_phy_data_width;

	switch (width) {
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_8:
		valid = (param == 8);
		break;
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_16:
		valid = (param == 16);
		break;
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_8_OR_16:
		valid = (param == 8 || param == 16);
		break;
	}

	if (!valid)
		dwc2_set_param_phy_utmi_width(hsotg);
}