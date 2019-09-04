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
struct phy_berlin_usb_priv {int pll_divider; scalar_t__ base; int /*<<< orphan*/  rst_ctrl; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int ACK_LENGTH_16_CL ; 
 int ANA_TEST_DC_CTRL (int) ; 
 int CLK_BLK_EN ; 
 int CLK_STABLE ; 
 int DISCON_THRESHOLD_270 ; 
 int DRV_SLEWRATE (int) ; 
 int EXT_FS_RCAL_DIV (int) ; 
 int EXT_HS_RCAL_EN ; 
 int EXT_RS_RCAL_DIV (int) ; 
 int FS_DRV_EN_MASK (int) ; 
 int IMPCAL_VTH_DIV (int) ; 
 int IMP_CAL_FS_HS_DLY_3 ; 
 int INTPL_CUR_30 ; 
 int KVC0_REG_CTRL ; 
 int LPF_COEF (int) ; 
 int PHASE_FREEZE_DLY_4_CL ; 
 int PHASE_OFF_TOL_250 ; 
 int PLL_CTRL_REG ; 
 int R_ROTATE_0 ; 
 int SQ_LENGTH_12 ; 
 int SQ_THRESHOLD (int) ; 
 int TX_CHAN_CTRL_REG (int) ; 
 int TX_OUT_AMP (int) ; 
 int TX_VDD12_13 ; 
 scalar_t__ USB_PHY_ANALOG ; 
 scalar_t__ USB_PHY_PLL ; 
 scalar_t__ USB_PHY_PLL_CONTROL ; 
 scalar_t__ USB_PHY_RX_CTRL ; 
 scalar_t__ USB_PHY_TX_CTRL0 ; 
 scalar_t__ USB_PHY_TX_CTRL1 ; 
 scalar_t__ USB_PHY_TX_CTRL2 ; 
 int V2I_VCO_RATIO (int) ; 
 struct phy_berlin_usb_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int phy_berlin_usb_power_on(struct phy *phy)
{
	struct phy_berlin_usb_priv *priv = phy_get_drvdata(phy);

	reset_control_reset(priv->rst_ctrl);

	writel(priv->pll_divider,
	       priv->base + USB_PHY_PLL);
	writel(CLK_STABLE | PLL_CTRL_REG | PHASE_OFF_TOL_250 | KVC0_REG_CTRL |
	       CLK_BLK_EN, priv->base + USB_PHY_PLL_CONTROL);
	writel(V2I_VCO_RATIO(0x5) | R_ROTATE_0 | ANA_TEST_DC_CTRL(0x5),
	       priv->base + USB_PHY_ANALOG);
	writel(PHASE_FREEZE_DLY_4_CL | ACK_LENGTH_16_CL | SQ_LENGTH_12 |
	       DISCON_THRESHOLD_270 | SQ_THRESHOLD(0xa) | LPF_COEF(0x2) |
	       INTPL_CUR_30, priv->base + USB_PHY_RX_CTRL);

	writel(TX_VDD12_13 | TX_OUT_AMP(0x3), priv->base + USB_PHY_TX_CTRL1);
	writel(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4),
	       priv->base + USB_PHY_TX_CTRL0);

	writel(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4) |
	       EXT_FS_RCAL_DIV(0x2), priv->base + USB_PHY_TX_CTRL0);

	writel(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4),
	       priv->base + USB_PHY_TX_CTRL0);
	writel(TX_CHAN_CTRL_REG(0xf) | DRV_SLEWRATE(0x3) | IMP_CAL_FS_HS_DLY_3 |
	       FS_DRV_EN_MASK(0xd), priv->base + USB_PHY_TX_CTRL2);

	return 0;
}