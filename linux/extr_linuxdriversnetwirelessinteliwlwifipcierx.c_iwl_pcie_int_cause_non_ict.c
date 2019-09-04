#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT ; 
 TYPE_1__* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_pcie_int_cause_non_ict(struct iwl_trans *trans)
{
	u32 inta;

	lockdep_assert_held(&IWL_TRANS_GET_PCIE_TRANS(trans)->irq_lock);

	trace_iwlwifi_dev_irq(trans->dev);

	/* Discover which interrupts are active/pending */
	inta = iwl_read32(trans, CSR_INT);

	/* the thread will service interrupts and re-enable them */
	return inta;
}