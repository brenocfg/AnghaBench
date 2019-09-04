#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int frnum; } ;
struct TYPE_16__ {TYPE_4__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_5__ hfnum_data_t ;
struct TYPE_14__ {int oddfrm; } ;
struct TYPE_17__ {TYPE_3__ b; } ;
typedef  TYPE_6__ hcchar_data_t ;
struct TYPE_18__ {TYPE_2__* host_if; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_19__ {scalar_t__ ep_type; } ;
typedef  TYPE_8__ dwc_hc_t ;
struct TYPE_13__ {TYPE_1__* host_global_regs; } ;
struct TYPE_12__ {int /*<<< orphan*/  hfnum; } ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_TYPE_INTR ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hc_set_even_odd_frame(dwc_otg_core_if_t * core_if,
					 dwc_hc_t * hc, hcchar_data_t * hcchar)
{
	if (hc->ep_type == DWC_OTG_EP_TYPE_INTR ||
	    hc->ep_type == DWC_OTG_EP_TYPE_ISOC) {
		hfnum_data_t hfnum;
		hfnum.d32 =
		    DWC_READ_REG32(&core_if->host_if->host_global_regs->hfnum);

		/* 1 if _next_ frame is odd, 0 if it's even */
		hcchar->b.oddfrm = (hfnum.b.frnum & 0x1) ? 0 : 1;
#ifdef DEBUG
		if (hc->ep_type == DWC_OTG_EP_TYPE_INTR && hc->do_split
		    && !hc->complete_split) {
			switch (hfnum.b.frnum & 0x7) {
			case 7:
				core_if->hfnum_7_samples++;
				core_if->hfnum_7_frrem_accum += hfnum.b.frrem;
				break;
			case 0:
				core_if->hfnum_0_samples++;
				core_if->hfnum_0_frrem_accum += hfnum.b.frrem;
				break;
			default:
				core_if->hfnum_other_samples++;
				core_if->hfnum_other_frrem_accum +=
				    hfnum.b.frrem;
				break;
			}
		}
#endif
	}
}