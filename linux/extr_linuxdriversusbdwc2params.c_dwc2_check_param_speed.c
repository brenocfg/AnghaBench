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
struct TYPE_2__ {int phy_type; int speed; } ;
struct dwc2_hsotg {TYPE_1__ params; } ;

/* Variables and functions */
 int DWC2_PHY_TYPE_PARAM_FS ; 
#define  DWC2_SPEED_PARAM_FULL 130 
#define  DWC2_SPEED_PARAM_HIGH 129 
#define  DWC2_SPEED_PARAM_LOW 128 
 int /*<<< orphan*/  dwc2_set_param_speed (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_check_param_speed(struct dwc2_hsotg *hsotg)
{
	int valid = 1;
	int phy_type = hsotg->params.phy_type;
	int speed = hsotg->params.speed;

	switch (speed) {
	case DWC2_SPEED_PARAM_HIGH:
		if ((hsotg->params.speed == DWC2_SPEED_PARAM_HIGH) &&
		    (phy_type == DWC2_PHY_TYPE_PARAM_FS))
			valid = 0;
		break;
	case DWC2_SPEED_PARAM_FULL:
	case DWC2_SPEED_PARAM_LOW:
		break;
	default:
		valid = 0;
		break;
	}

	if (!valid)
		dwc2_set_param_speed(hsotg);
}