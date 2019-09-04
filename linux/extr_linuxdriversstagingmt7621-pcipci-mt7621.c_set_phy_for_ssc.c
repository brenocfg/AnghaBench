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
struct mt7621_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ RALINK_PCIEPHY_P0P1_CTL_OFFSET ; 
 scalar_t__ RALINK_PCIEPHY_P2_CTL_OFFSET ; 
 int /*<<< orphan*/  SYSC_REG_SYSTEM_CONFIG0 ; 
 int /*<<< orphan*/  printk (char*) ; 
 unsigned long rt_sysc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pcie_phy (struct mt7621_pcie*,scalar_t__,int,int,int) ; 

void
set_phy_for_ssc(struct mt7621_pcie *pcie)
{
	unsigned long reg = rt_sysc_r32(SYSC_REG_SYSTEM_CONFIG0);

	reg = (reg >> 6) & 0x7;
	/* Set PCIe Port0 & Port1 PHY to disable SSC */
	/* Debug Xtal Type */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x400),  8, 1, 0x01);	// rg_pe1_frc_h_xtal_type
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x400),  9, 2, 0x00);	// rg_pe1_h_xtal_type
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x000),  4, 1, 0x01);	// rg_pe1_frc_phy_en	//Force Port 0 enable control
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x100),  4, 1, 0x01);	// rg_pe1_frc_phy_en	//Force Port 1 enable control
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x000),  5, 1, 0x00);	// rg_pe1_phy_en	//Port 0 disable
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x100),  5, 1, 0x00);	// rg_pe1_phy_en	//Port 1 disable
	if (reg <= 5 && reg >= 3) {	// 40MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490),  6, 2, 0x01);	// RG_PE1_H_PLL_PREDIV	//Pre-divider ratio (for host mode)
		printk("***** Xtal 40MHz *****\n");
	} else {			// 25MHz | 20MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490),  6, 2, 0x00);	// RG_PE1_H_PLL_PREDIV	//Pre-divider ratio (for host mode)
		if (reg >= 6) {
			printk("***** Xtal 25MHz *****\n");
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4bc),  4, 2, 0x01);	// RG_PE1_H_PLL_FBKSEL	//Feedback clock select
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x49c),  0, 31, 0x18000000);	// RG_PE1_H_LCDDS_PCW_NCPO	//DDS NCPO PCW (for host mode)
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4a4),  0, 16, 0x18d);	// RG_PE1_H_LCDDS_SSC_PRD	//DDS SSC dither period control
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4a8),  0, 12, 0x4a);	// RG_PE1_H_LCDDS_SSC_DELTA	//DDS SSC dither amplitude control
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4a8), 16, 12, 0x4a);	// RG_PE1_H_LCDDS_SSC_DELTA1	//DDS SSC dither amplitude control for initial
		} else {
			printk("***** Xtal 20MHz *****\n");
		}
	}
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4a0),  5, 1, 0x01);	// RG_PE1_LCDDS_CLK_PH_INV	//DDS clock inversion
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490), 22, 2, 0x02);	// RG_PE1_H_PLL_BC
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490), 18, 4, 0x06);	// RG_PE1_H_PLL_BP
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490), 12, 4, 0x02);	// RG_PE1_H_PLL_IR
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490),  8, 4, 0x01);	// RG_PE1_H_PLL_IC
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x4ac), 16, 3, 0x00);	// RG_PE1_H_PLL_BR
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x490),  1, 3, 0x02);	// RG_PE1_PLL_DIVEN
	if (reg <= 5 && reg >= 3) {	// 40MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x414),  6, 2, 0x01);	// rg_pe1_mstckdiv		//value of da_pe1_mstckdiv when force mode enable
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x414),  5, 1, 0x01);	// rg_pe1_frc_mstckdiv	//force mode enable of da_pe1_mstckdiv
	}
	/* Enable PHY and disable force mode */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x000),  5, 1, 0x01);	// rg_pe1_phy_en	//Port 0 enable
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x100),  5, 1, 0x01);	// rg_pe1_phy_en	//Port 1 enable
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x000),  4, 1, 0x00);	// rg_pe1_frc_phy_en	//Force Port 0 disable control
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x100),  4, 1, 0x00);	// rg_pe1_frc_phy_en	//Force Port 1 disable control

	/* Set PCIe Port2 PHY to disable SSC */
	/* Debug Xtal Type */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x400),  8, 1, 0x01);	// rg_pe1_frc_h_xtal_type
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x400),  9, 2, 0x00);	// rg_pe1_h_xtal_type
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x000),  4, 1, 0x01);	// rg_pe1_frc_phy_en	//Force Port 0 enable control
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x000),  5, 1, 0x00);	// rg_pe1_phy_en	//Port 0 disable
	if (reg <= 5 && reg >= 3) {	// 40MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490),  6, 2, 0x01);	// RG_PE1_H_PLL_PREDIV	//Pre-divider ratio (for host mode)
	} else {			// 25MHz | 20MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490),  6, 2, 0x00);	// RG_PE1_H_PLL_PREDIV	//Pre-divider ratio (for host mode)
		if (reg >= 6) {		// 25MHz Xtal
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4bc),  4, 2, 0x01);	// RG_PE1_H_PLL_FBKSEL	//Feedback clock select
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x49c),  0, 31, 0x18000000);	// RG_PE1_H_LCDDS_PCW_NCPO	//DDS NCPO PCW (for host mode)
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4a4),  0, 16, 0x18d);	// RG_PE1_H_LCDDS_SSC_PRD	//DDS SSC dither period control
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4a8),  0, 12, 0x4a);	// RG_PE1_H_LCDDS_SSC_DELTA	//DDS SSC dither amplitude control
			set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4a8), 16, 12, 0x4a);	// RG_PE1_H_LCDDS_SSC_DELTA1	//DDS SSC dither amplitude control for initial
		}
	}
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4a0),  5, 1, 0x01);	// RG_PE1_LCDDS_CLK_PH_INV	//DDS clock inversion
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490), 22, 2, 0x02);	// RG_PE1_H_PLL_BC
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490), 18, 4, 0x06);	// RG_PE1_H_PLL_BP
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490), 12, 4, 0x02);	// RG_PE1_H_PLL_IR
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490),  8, 4, 0x01);	// RG_PE1_H_PLL_IC
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x4ac), 16, 3, 0x00);	// RG_PE1_H_PLL_BR
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x490),  1, 3, 0x02);	// RG_PE1_PLL_DIVEN
	if (reg <= 5 && reg >= 3) {	// 40MHz Xtal
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x414),  6, 2, 0x01);	// rg_pe1_mstckdiv		//value of da_pe1_mstckdiv when force mode enable
		set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x414),  5, 1, 0x01);	// rg_pe1_frc_mstckdiv	//force mode enable of da_pe1_mstckdiv
	}
	/* Enable PHY and disable force mode */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x000),  5, 1, 0x01);	// rg_pe1_phy_en	//Port 0 enable
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x000),  4, 1, 0x00);	// rg_pe1_frc_phy_en	//Force Port 0 disable control
}