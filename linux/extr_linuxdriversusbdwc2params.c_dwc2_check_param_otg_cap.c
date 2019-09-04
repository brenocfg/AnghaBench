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
struct TYPE_4__ {int op_mode; } ;
struct TYPE_3__ {int otg_cap; } ;
struct dwc2_hsotg {TYPE_2__ hw_params; TYPE_1__ params; } ;

/* Variables and functions */
#define  DWC2_CAP_PARAM_HNP_SRP_CAPABLE 134 
#define  DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE 133 
#define  DWC2_CAP_PARAM_SRP_ONLY_CAPABLE 132 
#define  GHWCFG2_OP_MODE_HNP_SRP_CAPABLE 131 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE 130 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_HOST 129 
#define  GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE 128 
 int /*<<< orphan*/  dwc2_set_param_otg_cap (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_check_param_otg_cap(struct dwc2_hsotg *hsotg)
{
	int valid = 1;

	switch (hsotg->params.otg_cap) {
	case DWC2_CAP_PARAM_HNP_SRP_CAPABLE:
		if (hsotg->hw_params.op_mode != GHWCFG2_OP_MODE_HNP_SRP_CAPABLE)
			valid = 0;
		break;
	case DWC2_CAP_PARAM_SRP_ONLY_CAPABLE:
		switch (hsotg->hw_params.op_mode) {
		case GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		case GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
		case GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
		case GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
			break;
		default:
			valid = 0;
			break;
		}
		break;
	case DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE:
		/* always valid */
		break;
	default:
		valid = 0;
		break;
	}

	if (!valid)
		dwc2_set_param_otg_cap(hsotg);
}