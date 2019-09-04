#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sgiseeq_regs {int dummy; } ;
struct sgiseeq_private {scalar_t__ rx_new; scalar_t__ rx_desc; } ;
struct hpc3_ethregs {int rx_ctrl; int /*<<< orphan*/  rx_ndptr; } ;

/* Variables and functions */
 int HPC3_ERXCTRL_ACTIVE ; 
 int /*<<< orphan*/  VIRT_TO_DMA (struct sgiseeq_private*,scalar_t__) ; 
 int /*<<< orphan*/  seeq_go (struct sgiseeq_private*,struct hpc3_ethregs*,struct sgiseeq_regs*) ; 

__attribute__((used)) static inline void rx_maybe_restart(struct sgiseeq_private *sp,
				    struct hpc3_ethregs *hregs,
				    struct sgiseeq_regs *sregs)
{
	if (!(hregs->rx_ctrl & HPC3_ERXCTRL_ACTIVE)) {
		hregs->rx_ndptr = VIRT_TO_DMA(sp, sp->rx_desc + sp->rx_new);
		seeq_go(sp, hregs, sregs);
	}
}