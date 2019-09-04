#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {TYPE_2__** in_ep_regs; TYPE_1__* dev_global_regs; } ;
typedef  TYPE_3__ dwc_otg_dev_if_t ;
struct TYPE_11__ {scalar_t__ multiproc_int_enable; TYPE_3__* dev_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_12__ {size_t num; } ;
typedef  TYPE_5__ dwc_ep_t ;
struct TYPE_9__ {int /*<<< orphan*/  diepint; } ;
struct TYPE_8__ {int /*<<< orphan*/  dtknqr4_fifoemptymsk; int /*<<< orphan*/  diepmsk; int /*<<< orphan*/ * diepeachintmsk; } ;

/* Variables and functions */
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t dwc_otg_read_dev_in_ep_intr(dwc_otg_core_if_t * core_if,
						   dwc_ep_t * ep)
{
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	uint32_t v, msk, emp;

	if (core_if->multiproc_int_enable) {
		msk =
		    DWC_READ_REG32(&dev_if->
				   dev_global_regs->diepeachintmsk[ep->num]);
		emp =
		    DWC_READ_REG32(&dev_if->
				   dev_global_regs->dtknqr4_fifoemptymsk);
		msk |= ((emp >> ep->num) & 0x1) << 7;
		v = DWC_READ_REG32(&dev_if->in_ep_regs[ep->num]->diepint) & msk;
	} else {
		msk = DWC_READ_REG32(&dev_if->dev_global_regs->diepmsk);
		emp =
		    DWC_READ_REG32(&dev_if->
				   dev_global_regs->dtknqr4_fifoemptymsk);
		msk |= ((emp >> ep->num) & 0x1) << 7;
		v = DWC_READ_REG32(&dev_if->in_ep_regs[ep->num]->diepint) & msk;
	}

	return v;
}