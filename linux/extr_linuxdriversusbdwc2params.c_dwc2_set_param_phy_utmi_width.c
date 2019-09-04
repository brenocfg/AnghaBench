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
struct TYPE_4__ {int phy_utmi_width; } ;
struct TYPE_3__ {scalar_t__ utmi_phy_data_width; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
 scalar_t__ GHWCFG4_UTMI_PHY_DATA_WIDTH_8 ; 

__attribute__((used)) static void dwc2_set_param_phy_utmi_width(struct dwc2_hsotg *hsotg)
{
	int val;

	val = (hsotg->hw_params.utmi_phy_data_width ==
	       GHWCFG4_UTMI_PHY_DATA_WIDTH_8) ? 8 : 16;

	hsotg->params.phy_utmi_width = val;
}