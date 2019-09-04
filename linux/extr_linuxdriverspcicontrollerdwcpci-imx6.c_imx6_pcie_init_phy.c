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
struct imx6_pcie {int variant; int tx_deemph_gen1; int tx_deemph_gen2_3p5db; int tx_deemph_gen2_6db; int tx_swing_full; int tx_swing_low; int /*<<< orphan*/  iomuxc_gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX6Q_GPR12_DEVICE_TYPE ; 
 int /*<<< orphan*/  IMX6Q_GPR12_LOS_LEVEL ; 
 int /*<<< orphan*/  IMX6Q_GPR12_PCIE_CTL_2 ; 
 int /*<<< orphan*/  IMX6Q_GPR8_TX_DEEMPH_GEN1 ; 
 int /*<<< orphan*/  IMX6Q_GPR8_TX_DEEMPH_GEN2_3P5DB ; 
 int /*<<< orphan*/  IMX6Q_GPR8_TX_DEEMPH_GEN2_6DB ; 
 int /*<<< orphan*/  IMX6Q_GPR8_TX_SWING_FULL ; 
 int /*<<< orphan*/  IMX6Q_GPR8_TX_SWING_LOW ; 
#define  IMX6SX 129 
 int IMX6SX_GPR12_PCIE_RX_EQ_2 ; 
 int /*<<< orphan*/  IMX6SX_GPR12_PCIE_RX_EQ_MASK ; 
#define  IMX7D 128 
 int /*<<< orphan*/  IMX7D_GPR12_PCIE_PHY_REFCLK_SEL ; 
 int /*<<< orphan*/  IOMUXC_GPR12 ; 
 int /*<<< orphan*/  IOMUXC_GPR8 ; 
 int PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imx6_pcie_init_phy(struct imx6_pcie *imx6_pcie)
{
	switch (imx6_pcie->variant) {
	case IMX7D:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX7D_GPR12_PCIE_PHY_REFCLK_SEL, 0);
		break;
	case IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_RX_EQ_MASK,
				   IMX6SX_GPR12_PCIE_RX_EQ_2);
		/* FALLTHROUGH */
	default:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2, 0 << 10);

		/* configure constant input signal to the pcie ctrl and phy */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_LOS_LEVEL, 9 << 4);

		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN1,
				   imx6_pcie->tx_deemph_gen1 << 0);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_3P5DB,
				   imx6_pcie->tx_deemph_gen2_3p5db << 6);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_6DB,
				   imx6_pcie->tx_deemph_gen2_6db << 12);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_FULL,
				   imx6_pcie->tx_swing_full << 18);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_LOW,
				   imx6_pcie->tx_swing_low << 25);
		break;
	}

	regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
			IMX6Q_GPR12_DEVICE_TYPE, PCI_EXP_TYPE_ROOT_PORT << 12);
}