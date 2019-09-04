#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_10__ {TYPE_2__* dev_if; scalar_t__ multiproc_int_enable; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int nyet; } ;
struct TYPE_11__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_5__ doepmsk_data_t ;
struct TYPE_8__ {TYPE_1__* dev_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  doepmsk; int /*<<< orphan*/ * doepeachintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,char*) ; 
 TYPE_4__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int32_t handle_out_ep_nyet_intr(dwc_otg_pcd_t * pcd,
					      const uint32_t epnum)
{
	/** @todo implement ISR */
	dwc_otg_core_if_t *core_if;
	doepmsk_data_t intr_mask = {.d32 = 0 };

	DWC_PRINTF("INTERRUPT Handler not implemented for %s\n", "OUT EP NYET");
	core_if = GET_CORE_IF(pcd);
	intr_mask.b.nyet = 1;

	if (core_if->multiproc_int_enable) {
		DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->
				 doepeachintmsk[epnum], intr_mask.d32, 0);
	} else {
		DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->doepmsk,
				 intr_mask.d32, 0);
	}

	return 1;
}