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
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  pss_err_status_reg; int /*<<< orphan*/  ll_halt; } ;
struct TYPE_7__ {int /*<<< orphan*/  device_id; } ;
struct TYPE_11__ {TYPE_2__ ioc_regs; TYPE_1__ pcidev; } ;
struct TYPE_9__ {int /*<<< orphan*/  intr_status; } ;
struct TYPE_10__ {TYPE_3__ bfa_regs; } ;
struct bfa_s {TYPE_5__ ioc; TYPE_4__ iocfc; } ;
typedef  int bfa_boolean_t ;

/* Variables and functions */
 int __FW_INIT_HALT_P ; 
 int __HFN_INT_CPQ_HALT_CT2 ; 
 int __HFN_INT_ERR_MASK ; 
 int __HFN_INT_ERR_MASK_CT2 ; 
 int __HFN_INT_ERR_PSS ; 
 int __HFN_INT_ERR_PSS_CT2 ; 
 int __HFN_INT_LL_HALT ; 
 int __HFN_INT_MBOX_LPU0 ; 
 int __HFN_INT_MBOX_LPU0_CT2 ; 
 int __HFN_INT_MBOX_LPU1 ; 
 int __HFN_INT_MBOX_LPU1_CT2 ; 
 scalar_t__ bfa_asic_id_ct (int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_asic_id_ct2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_error_isr (TYPE_5__*) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_isr (TYPE_5__*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void
bfa_msix_lpu_err(struct bfa_s *bfa, int vec)
{
	u32 intr, curr_value;
	bfa_boolean_t lpu_isr, halt_isr, pss_isr;

	intr = readl(bfa->iocfc.bfa_regs.intr_status);

	if (bfa_asic_id_ct2(bfa->ioc.pcidev.device_id)) {
		halt_isr = intr & __HFN_INT_CPQ_HALT_CT2;
		pss_isr  = intr & __HFN_INT_ERR_PSS_CT2;
		lpu_isr  = intr & (__HFN_INT_MBOX_LPU0_CT2 |
				   __HFN_INT_MBOX_LPU1_CT2);
		intr    &= __HFN_INT_ERR_MASK_CT2;
	} else {
		halt_isr = bfa_asic_id_ct(bfa->ioc.pcidev.device_id) ?
					  (intr & __HFN_INT_LL_HALT) : 0;
		pss_isr  = intr & __HFN_INT_ERR_PSS;
		lpu_isr  = intr & (__HFN_INT_MBOX_LPU0 | __HFN_INT_MBOX_LPU1);
		intr    &= __HFN_INT_ERR_MASK;
	}

	if (lpu_isr)
		bfa_ioc_mbox_isr(&bfa->ioc);

	if (intr) {
		if (halt_isr) {
			/*
			 * If LL_HALT bit is set then FW Init Halt LL Port
			 * Register needs to be cleared as well so Interrupt
			 * Status Register will be cleared.
			 */
			curr_value = readl(bfa->ioc.ioc_regs.ll_halt);
			curr_value &= ~__FW_INIT_HALT_P;
			writel(curr_value, bfa->ioc.ioc_regs.ll_halt);
		}

		if (pss_isr) {
			/*
			 * ERR_PSS bit needs to be cleared as well in case
			 * interrups are shared so driver's interrupt handler is
			 * still called even though it is already masked out.
			 */
			curr_value = readl(
					bfa->ioc.ioc_regs.pss_err_status_reg);
			writel(curr_value,
				bfa->ioc.ioc_regs.pss_err_status_reg);
		}

		writel(intr, bfa->iocfc.bfa_regs.intr_status);
		bfa_ioc_error_isr(&bfa->ioc);
	}
}