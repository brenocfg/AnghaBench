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
struct phy {int dummy; } ;
struct hisi_inno_phy_priv {int /*<<< orphan*/  por_rst; int /*<<< orphan*/  ref_clk; } ;
struct hisi_inno_phy_port {int /*<<< orphan*/  utmi_rst; struct hisi_inno_phy_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  POR_RST_COMPLETE_TIME ; 
 int /*<<< orphan*/  REF_CLK_STABLE_TIME ; 
 int /*<<< orphan*/  UTMI_RST_COMPLETE_TIME ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_inno_phy_setup (struct hisi_inno_phy_priv*) ; 
 struct hisi_inno_phy_port* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_inno_phy_init(struct phy *phy)
{
	struct hisi_inno_phy_port *port = phy_get_drvdata(phy);
	struct hisi_inno_phy_priv *priv = port->priv;
	int ret;

	ret = clk_prepare_enable(priv->ref_clk);
	if (ret)
		return ret;
	udelay(REF_CLK_STABLE_TIME);

	reset_control_deassert(priv->por_rst);
	udelay(POR_RST_COMPLETE_TIME);

	/* Set up phy registers */
	hisi_inno_phy_setup(priv);

	reset_control_deassert(port->utmi_rst);
	udelay(UTMI_RST_COMPLETE_TIME);

	return 0;
}