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
struct ti_pipe3 {int /*<<< orphan*/  phy_rx; } ;

/* Variables and functions */
 int INTERFACE_MASK ; 
 int INTERFACE_SHIFT ; 
 int LOSD_MASK ; 
 int LOSD_SHIFT ; 
 int MEM_CDR_CDR_2NDO_SDM_MODE ; 
 int MEM_CDR_FASTLOCK ; 
 int MEM_CDR_LBW ; 
 int MEM_CDR_STEPCNT ; 
 int MEM_CDR_STL_MASK ; 
 int MEM_CDR_STL_SHIFT ; 
 int MEM_CDR_THR_MASK ; 
 int MEM_CDR_THR_MODE ; 
 int MEM_CDR_THR_SHIFT ; 
 int MEM_DLL_PHINT_RATE ; 
 int MEM_DLL_TRIM_SEL ; 
 int MEM_DLL_TRIM_SHIFT ; 
 int MEM_EQCTL ; 
 int MEM_EQCTL_SHIFT ; 
 int MEM_EQFTC ; 
 int MEM_EQLEV ; 
 int MEM_OVRD_EQFTC ; 
 int MEM_OVRD_EQLEV ; 
 int MEM_OVRD_HS_RATE ; 
 int MEM_PLLDIV ; 
 int /*<<< orphan*/  PCIEPHYRX_ANA_PROGRAMMABILITY ; 
 int /*<<< orphan*/  PCIEPHYRX_DIGITAL_MODES ; 
 int /*<<< orphan*/  PCIEPHYRX_DLL ; 
 int /*<<< orphan*/  PCIEPHYRX_EQUALIZER ; 
 int /*<<< orphan*/  PCIEPHYRX_TRIM ; 
 int ti_pipe3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pipe3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ti_pipe3_calibrate(struct ti_pipe3 *phy)
{
	u32 val;

	val = ti_pipe3_readl(phy->phy_rx, PCIEPHYRX_ANA_PROGRAMMABILITY);
	val &= ~(INTERFACE_MASK | LOSD_MASK | MEM_PLLDIV);
	val = (0x1 << INTERFACE_SHIFT | 0xA << LOSD_SHIFT);
	ti_pipe3_writel(phy->phy_rx, PCIEPHYRX_ANA_PROGRAMMABILITY, val);

	val = ti_pipe3_readl(phy->phy_rx, PCIEPHYRX_DIGITAL_MODES);
	val &= ~(MEM_CDR_STEPCNT | MEM_CDR_STL_MASK | MEM_CDR_THR_MASK |
		 MEM_CDR_CDR_2NDO_SDM_MODE | MEM_OVRD_HS_RATE);
	val |= (MEM_CDR_FASTLOCK | MEM_CDR_LBW | 0x3 << MEM_CDR_STL_SHIFT |
		0x1 << MEM_CDR_THR_SHIFT | MEM_CDR_THR_MODE);
	ti_pipe3_writel(phy->phy_rx, PCIEPHYRX_DIGITAL_MODES, val);

	val = ti_pipe3_readl(phy->phy_rx, PCIEPHYRX_TRIM);
	val &= ~MEM_DLL_TRIM_SEL;
	val |= 0x2 << MEM_DLL_TRIM_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PCIEPHYRX_TRIM, val);

	val = ti_pipe3_readl(phy->phy_rx, PCIEPHYRX_DLL);
	val |= MEM_DLL_PHINT_RATE;
	ti_pipe3_writel(phy->phy_rx, PCIEPHYRX_DLL, val);

	val = ti_pipe3_readl(phy->phy_rx, PCIEPHYRX_EQUALIZER);
	val &= ~(MEM_EQLEV | MEM_EQCTL | MEM_OVRD_EQLEV | MEM_OVRD_EQFTC);
	val |= MEM_EQFTC | 0x1 << MEM_EQCTL_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PCIEPHYRX_EQUALIZER, val);
}