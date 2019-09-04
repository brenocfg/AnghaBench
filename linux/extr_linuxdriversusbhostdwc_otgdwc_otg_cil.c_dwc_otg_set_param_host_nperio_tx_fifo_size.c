#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {TYPE_2__* core_params; TYPE_1__* core_global_regs; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_6__ {int host_nperio_tx_fifo_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  gnptxfsiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int,int) ; 
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_host_nperio_tx_fifo_size(dwc_otg_core_if_t * core_if,
					       int32_t val)
{
	int retval = 0;

	if (DWC_OTG_PARAM_TEST(val, 16, 32768)) {
		DWC_WARN("Wrong value for host_nperio_tx_fifo_size\n");
		DWC_WARN("host_nperio_tx_fifo_size must be 16-32768\n");
		return -DWC_E_INVALID;
	}

	if (val > (DWC_READ_REG32(&core_if->core_global_regs->gnptxfsiz) >> 16)) {
		if (dwc_otg_param_initialized
		    (core_if->core_params->host_nperio_tx_fifo_size)) {
			DWC_ERROR
			    ("%d invalid for host_nperio_tx_fifo_size. Check HW configuration.\n",
			     val);
		}
		val =
		    (DWC_READ_REG32(&core_if->core_global_regs->gnptxfsiz) >>
		     16);
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->host_nperio_tx_fifo_size = val;
	return retval;
}