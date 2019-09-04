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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int hw_rev; } ;

/* Variables and functions */
#define  ATH10K_HW_QCA4019 136 
#define  ATH10K_HW_QCA6174 135 
#define  ATH10K_HW_QCA9377 134 
#define  ATH10K_HW_QCA9887 133 
#define  ATH10K_HW_QCA9888 132 
#define  ATH10K_HW_QCA988X 131 
#define  ATH10K_HW_QCA9984 130 
#define  ATH10K_HW_QCA99X0 129 
#define  ATH10K_HW_WCN3990 128 
 scalar_t__ CORE_CTRL_ADDRESS ; 
 int /*<<< orphan*/  CORE_CTRL_PCIE_REG_31_MASK ; 
 scalar_t__ SOC_CORE_BASE_ADDRESS ; 
 int /*<<< orphan*/  ath10k_pci_read32 (struct ath10k*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,int /*<<< orphan*/ ) ; 

void ath10k_pci_irq_msi_fw_mask(struct ath10k *ar)
{
	u32 val;

	switch (ar->hw_rev) {
	case ATH10K_HW_QCA988X:
	case ATH10K_HW_QCA9887:
	case ATH10K_HW_QCA6174:
	case ATH10K_HW_QCA9377:
		val = ath10k_pci_read32(ar, SOC_CORE_BASE_ADDRESS +
					CORE_CTRL_ADDRESS);
		val &= ~CORE_CTRL_PCIE_REG_31_MASK;
		ath10k_pci_write32(ar, SOC_CORE_BASE_ADDRESS +
				   CORE_CTRL_ADDRESS, val);
		break;
	case ATH10K_HW_QCA99X0:
	case ATH10K_HW_QCA9984:
	case ATH10K_HW_QCA9888:
	case ATH10K_HW_QCA4019:
		/* TODO: Find appropriate register configuration for QCA99X0
		 *  to mask irq/MSI.
		 */
		break;
	case ATH10K_HW_WCN3990:
		break;
	}
}