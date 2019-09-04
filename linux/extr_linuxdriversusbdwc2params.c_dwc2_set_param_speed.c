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
struct TYPE_2__ {scalar_t__ phy_type; int speed; } ;
struct dwc2_hsotg {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ DWC2_PHY_TYPE_PARAM_FS ; 
 int DWC2_SPEED_PARAM_FULL ; 
 int DWC2_SPEED_PARAM_HIGH ; 
 scalar_t__ dwc2_is_fs_iot (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_is_hs_iot (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_set_param_speed(struct dwc2_hsotg *hsotg)
{
	int val;

	val = hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS ?
		DWC2_SPEED_PARAM_FULL : DWC2_SPEED_PARAM_HIGH;

	if (dwc2_is_fs_iot(hsotg))
		val = DWC2_SPEED_PARAM_FULL;

	if (dwc2_is_hs_iot(hsotg))
		val = DWC2_SPEED_PARAM_HIGH;

	hsotg->params.speed = val;
}