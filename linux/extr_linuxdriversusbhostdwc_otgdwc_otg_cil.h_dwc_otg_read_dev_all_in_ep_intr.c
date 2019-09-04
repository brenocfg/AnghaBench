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
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_2__* dev_if; scalar_t__ multiproc_int_enable; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_6__ {TYPE_1__* dev_global_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  daintmsk; int /*<<< orphan*/  daint; int /*<<< orphan*/  deachintmsk; int /*<<< orphan*/  deachint; } ;

/* Variables and functions */
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t dwc_otg_read_dev_all_in_ep_intr(dwc_otg_core_if_t *
						       core_if)
{

	uint32_t v;

	if (core_if->multiproc_int_enable) {
		v = DWC_READ_REG32(&core_if->dev_if->
				   dev_global_regs->deachint) &
		    DWC_READ_REG32(&core_if->
				   dev_if->dev_global_regs->deachintmsk);
	} else {
		v = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->daint) &
		    DWC_READ_REG32(&core_if->dev_if->dev_global_regs->daintmsk);
	}
	return (v & 0xffff);
}