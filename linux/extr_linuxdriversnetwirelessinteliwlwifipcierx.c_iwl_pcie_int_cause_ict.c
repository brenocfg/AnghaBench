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
typedef  int u32 ;
struct iwl_trans_pcie {size_t ict_index; scalar_t__* ict_tbl; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICT_COUNT ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*,size_t,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_ict_read (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_pcie_int_cause_ict(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 inta;
	u32 val = 0;
	u32 read;

	trace_iwlwifi_dev_irq(trans->dev);

	/* Ignore interrupt if there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic interrupts thrown from our NIC. */
	read = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
	trace_iwlwifi_dev_ict_read(trans->dev, trans_pcie->ict_index, read);
	if (!read)
		return 0;

	/*
	 * Collect all entries up to the first 0, starting from ict_index;
	 * note we already read at ict_index.
	 */
	do {
		val |= read;
		IWL_DEBUG_ISR(trans, "ICT index %d value 0x%08X\n",
				trans_pcie->ict_index, read);
		trans_pcie->ict_tbl[trans_pcie->ict_index] = 0;
		trans_pcie->ict_index =
			((trans_pcie->ict_index + 1) & (ICT_COUNT - 1));

		read = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
		trace_iwlwifi_dev_ict_read(trans->dev, trans_pcie->ict_index,
					   read);
	} while (read);

	/* We should not get this value, just ignore it. */
	if (val == 0xffffffff)
		val = 0;

	/*
	 * this is a w/a for a h/w bug. the h/w bug may cause the Rx bit
	 * (bit 15 before shifting it to 31) to clear when using interrupt
	 * coalescing. fortunately, bits 18 and 19 stay set when this happens
	 * so we use them to decide on the real state of the Rx bit.
	 * In order words, bit 15 is set if bit 18 or bit 19 are set.
	 */
	if (val & 0xC0000)
		val |= 0x8000;

	inta = (0xff & val) | ((0xff00 & val) << 16);
	return inta;
}