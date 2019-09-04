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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct phy {TYPE_1__ dev; } ;
struct hix5hd2_priv {scalar_t__ base; scalar_t__ peri_ctrl; } ;

/* Variables and functions */
 int AMPLITUDE_GEN1 ; 
 int AMPLITUDE_GEN1_SHIFT ; 
 int AMPLITUDE_GEN2 ; 
 int AMPLITUDE_GEN2_SHIFT ; 
 int AMPLITUDE_GEN3 ; 
 int AMPLITUDE_GEN3_SHIFT ; 
 int AMPLITUDE_MASK ; 
 int /*<<< orphan*/  BIT (int) ; 
 int GEN2_EN_SHIFT ; 
 int HALF_RATE_SHIFT ; 
 int MPLL_MULTIPLIER_50M ; 
 int MPLL_MULTIPLIER_MASK ; 
 int MPLL_MULTIPLIER_SHIFT ; 
 int PHY_CONFIG_SHIFT ; 
 int PHY_RESET ; 
 int PREEMPH_GEN1 ; 
 int PREEMPH_GEN1_SHIFT ; 
 int PREEMPH_GEN2 ; 
 int PREEMPH_GEN2_SHIFT ; 
 int PREEMPH_GEN3 ; 
 int PREEMPH_GEN3_SHIFT ; 
 int PREEMPH_MASK ; 
 int REF_SSP_EN ; 
 int REF_USE_PAD ; 
 scalar_t__ SATA_PHY0_CTLL ; 
 scalar_t__ SATA_PORT_PHYCTL ; 
 scalar_t__ SATA_PORT_PHYCTL1 ; 
 scalar_t__ SATA_PORT_PHYCTL2 ; 
 int SPEED_CTRL ; 
 int SPEED_MODE_GEN1 ; 
 int SPEED_MODE_GEN2 ; 
 int SPEED_MODE_GEN3 ; 
 int SPEED_MODE_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int of_property_read_u32_array (int /*<<< orphan*/ ,char*,int*,int) ; 
 struct hix5hd2_priv* phy_get_drvdata (struct phy*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int hix5hd2_sata_phy_init(struct phy *phy)
{
	struct hix5hd2_priv *priv = phy_get_drvdata(phy);
	u32 val, data[2];
	int ret;

	if (priv->peri_ctrl) {
		ret = of_property_read_u32_array(phy->dev.of_node,
						 "hisilicon,power-reg",
						 &data[0], 2);
		if (ret) {
			dev_err(&phy->dev, "Fail read hisilicon,power-reg\n");
			return ret;
		}

		regmap_update_bits(priv->peri_ctrl, data[0],
				   BIT(data[1]), BIT(data[1]));
	}

	/* reset phy */
	val = readl_relaxed(priv->base + SATA_PHY0_CTLL);
	val &= ~(MPLL_MULTIPLIER_MASK | REF_USE_PAD);
	val |= MPLL_MULTIPLIER_50M << MPLL_MULTIPLIER_SHIFT |
	       REF_SSP_EN | PHY_RESET;
	writel_relaxed(val, priv->base + SATA_PHY0_CTLL);
	msleep(20);
	val &= ~PHY_RESET;
	writel_relaxed(val, priv->base + SATA_PHY0_CTLL);

	val = readl_relaxed(priv->base + SATA_PORT_PHYCTL1);
	val &= ~AMPLITUDE_MASK;
	val |= AMPLITUDE_GEN3 << AMPLITUDE_GEN3_SHIFT |
	       AMPLITUDE_GEN2 << AMPLITUDE_GEN2_SHIFT |
	       AMPLITUDE_GEN1 << AMPLITUDE_GEN1_SHIFT;
	writel_relaxed(val, priv->base + SATA_PORT_PHYCTL1);

	val = readl_relaxed(priv->base + SATA_PORT_PHYCTL2);
	val &= ~PREEMPH_MASK;
	val |= PREEMPH_GEN3 << PREEMPH_GEN3_SHIFT |
	       PREEMPH_GEN2 << PREEMPH_GEN2_SHIFT |
	       PREEMPH_GEN1 << PREEMPH_GEN1_SHIFT;
	writel_relaxed(val, priv->base + SATA_PORT_PHYCTL2);

	/* ensure PHYCTRL setting takes effect */
	val = readl_relaxed(priv->base + SATA_PORT_PHYCTL);
	val &= ~SPEED_MODE_MASK;
	val |= SPEED_MODE_GEN1 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN1 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN1 << GEN2_EN_SHIFT | SPEED_CTRL;
	writel_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	msleep(20);
	val &= ~SPEED_MODE_MASK;
	val |= SPEED_MODE_GEN3 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN3 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN3 << GEN2_EN_SHIFT | SPEED_CTRL;
	writel_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	val &= ~(SPEED_MODE_MASK | SPEED_CTRL);
	val |= SPEED_MODE_GEN2 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN2 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN2 << GEN2_EN_SHIFT;
	writel_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	return 0;
}