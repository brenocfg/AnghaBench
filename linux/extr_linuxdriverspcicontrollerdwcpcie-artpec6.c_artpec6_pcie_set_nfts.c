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
struct dw_pcie {int dummy; } ;
struct artpec6_pcie {scalar_t__ variant; struct dw_pcie* pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_F_ASPM_CTRL_OFF ; 
 int /*<<< orphan*/  ACK_N_FTS (int) ; 
 int /*<<< orphan*/  ACK_N_FTS_MASK ; 
 scalar_t__ ARTPEC7 ; 
 int /*<<< orphan*/  FAST_TRAINING_SEQ (int) ; 
 int /*<<< orphan*/  FAST_TRAINING_SEQ_MASK ; 
 int /*<<< orphan*/  PCIE_LINK_WIDTH_SPEED_CONTROL ; 
 int /*<<< orphan*/  dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void artpec6_pcie_set_nfts(struct artpec6_pcie *artpec6_pcie)
{
	struct dw_pcie *pci = artpec6_pcie->pci;
	u32 val;

	if (artpec6_pcie->variant != ARTPEC7)
		return;

	/*
	 * Increase the N_FTS (Number of Fast Training Sequences)
	 * to be transmitted when transitioning from L0s to L0.
	 */
	val = dw_pcie_readl_dbi(pci, ACK_F_ASPM_CTRL_OFF);
	val &= ~ACK_N_FTS_MASK;
	val |= ACK_N_FTS(180);
	dw_pcie_writel_dbi(pci, ACK_F_ASPM_CTRL_OFF, val);

	/*
	 * Set the Number of Fast Training Sequences that the core
	 * advertises as its N_FTS during Gen2 or Gen3 link training.
	 */
	val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
	val &= ~FAST_TRAINING_SEQ_MASK;
	val |= FAST_TRAINING_SEQ(180);
	dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
}