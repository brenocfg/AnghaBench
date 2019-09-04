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
typedef  int u64 ;
typedef  int u32 ;
struct mobiveil_pcie {scalar_t__ ib_wins_configured; scalar_t__ ppio_wins; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMAP_CTRL_EN_SHIFT ; 
 int AMAP_CTRL_TYPE_SHIFT ; 
 int /*<<< orphan*/  PAB_EXT_PEX_AMAP_SIZEN (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_AXI_WIN (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_CTRL (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_PEX_WIN_H (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_PEX_WIN_L (int) ; 
 int /*<<< orphan*/  PAB_PEX_PIO_CTRL ; 
 int PIO_ENABLE_SHIFT ; 
 int csr_readl (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_writel (struct mobiveil_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lower_32_bits (int) ; 
 int read_paged_register (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 
 int /*<<< orphan*/  write_paged_register (struct mobiveil_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_ib_windows(struct mobiveil_pcie *pcie, int win_num,
		int pci_addr, u32 type, u64 size)
{
	int pio_ctrl_val;
	int amap_ctrl_dw;
	u64 size64 = ~(size - 1);

	if ((pcie->ib_wins_configured + 1) > pcie->ppio_wins) {
		dev_err(&pcie->pdev->dev,
			"ERROR: max inbound windows reached !\n");
		return;
	}

	pio_ctrl_val = csr_readl(pcie, PAB_PEX_PIO_CTRL);
	csr_writel(pcie,
		pio_ctrl_val | (1 << PIO_ENABLE_SHIFT), PAB_PEX_PIO_CTRL);
	amap_ctrl_dw = read_paged_register(pcie, PAB_PEX_AMAP_CTRL(win_num));
	amap_ctrl_dw = (amap_ctrl_dw | (type << AMAP_CTRL_TYPE_SHIFT));
	amap_ctrl_dw = (amap_ctrl_dw | (1 << AMAP_CTRL_EN_SHIFT));

	write_paged_register(pcie, amap_ctrl_dw | lower_32_bits(size64),
				PAB_PEX_AMAP_CTRL(win_num));

	write_paged_register(pcie, upper_32_bits(size64),
				PAB_EXT_PEX_AMAP_SIZEN(win_num));

	write_paged_register(pcie, pci_addr, PAB_PEX_AMAP_AXI_WIN(win_num));
	write_paged_register(pcie, pci_addr, PAB_PEX_AMAP_PEX_WIN_L(win_num));
	write_paged_register(pcie, 0, PAB_PEX_AMAP_PEX_WIN_H(win_num));
}