#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {scalar_t__ op_mode; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int otg_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG ; 
 scalar_t__ DWC_HWCFG2_OP_MODE_SRP_CAPABLE_DEVICE ; 
 scalar_t__ DWC_HWCFG2_OP_MODE_SRP_CAPABLE_HOST ; 
 scalar_t__ DWC_HWCFG2_OP_MODE_SRP_ONLY_CAPABLE_OTG ; 
#define  DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE 130 
#define  DWC_OTG_CAP_PARAM_NO_HNP_SRP_CAPABLE 129 
#define  DWC_OTG_CAP_PARAM_SRP_ONLY_CAPABLE 128 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_otg_cap(dwc_otg_core_if_t * core_if, int32_t val)
{
	int valid;
	int retval = 0;
	if (DWC_OTG_PARAM_TEST(val, 0, 2)) {
		DWC_WARN("Wrong value for otg_cap parameter\n");
		DWC_WARN("otg_cap parameter must be 0,1 or 2\n");
		retval = -DWC_E_INVALID;
		goto out;
	}

	valid = 1;
	switch (val) {
	case DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE:
		if (core_if->hwcfg2.b.op_mode !=
		    DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG)
			valid = 0;
		break;
	case DWC_OTG_CAP_PARAM_SRP_ONLY_CAPABLE:
		if ((core_if->hwcfg2.b.op_mode !=
		     DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG)
		    && (core_if->hwcfg2.b.op_mode !=
			DWC_HWCFG2_OP_MODE_SRP_ONLY_CAPABLE_OTG)
		    && (core_if->hwcfg2.b.op_mode !=
			DWC_HWCFG2_OP_MODE_SRP_CAPABLE_DEVICE)
		    && (core_if->hwcfg2.b.op_mode !=
			DWC_HWCFG2_OP_MODE_SRP_CAPABLE_HOST)) {
			valid = 0;
		}
		break;
	case DWC_OTG_CAP_PARAM_NO_HNP_SRP_CAPABLE:
		/* always valid */
		break;
	}
	if (!valid) {
		if (dwc_otg_param_initialized(core_if->core_params->otg_cap)) {
			DWC_ERROR
			    ("%d invalid for otg_cap paremter. Check HW configuration.\n",
			     val);
		}
		val =
		    (((core_if->hwcfg2.b.op_mode ==
		       DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG)
		      || (core_if->hwcfg2.b.op_mode ==
			  DWC_HWCFG2_OP_MODE_SRP_ONLY_CAPABLE_OTG)
		      || (core_if->hwcfg2.b.op_mode ==
			  DWC_HWCFG2_OP_MODE_SRP_CAPABLE_DEVICE)
		      || (core_if->hwcfg2.b.op_mode ==
			  DWC_HWCFG2_OP_MODE_SRP_CAPABLE_HOST)) ?
		     DWC_OTG_CAP_PARAM_SRP_ONLY_CAPABLE :
		     DWC_OTG_CAP_PARAM_NO_HNP_SRP_CAPABLE);
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->otg_cap = val;
out:
	return retval;
}