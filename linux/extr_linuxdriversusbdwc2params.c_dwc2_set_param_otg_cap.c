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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  otg_cap; } ;
struct TYPE_3__ {int op_mode; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_CAP_PARAM_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC2_CAP_PARAM_SRP_ONLY_CAPABLE ; 
#define  GHWCFG2_OP_MODE_HNP_SRP_CAPABLE 131 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE 130 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_HOST 129 
#define  GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE 128 

__attribute__((used)) static void dwc2_set_param_otg_cap(struct dwc2_hsotg *hsotg)
{
	u8 val;

	switch (hsotg->hw_params.op_mode) {
	case GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		val = DWC2_CAP_PARAM_HNP_SRP_CAPABLE;
		break;
	case GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
	case GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
	case GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
		val = DWC2_CAP_PARAM_SRP_ONLY_CAPABLE;
		break;
	default:
		val = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
		break;
	}

	hsotg->params.otg_cap = val;
}