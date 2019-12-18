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
struct mt753x_port_cfg {int speed; int phy_mode; scalar_t__ enabled; scalar_t__ force_link; scalar_t__ duplex; } ;
struct gsw_mt753x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BACKPR_EN ; 
 int BKOFF_EN ; 
 int EINVAL ; 
 int FORCE_DPX ; 
 int FORCE_LINK ; 
 int FORCE_MODE_DPX ; 
 int FORCE_MODE_LNK ; 
 int FORCE_MODE_RX_FC ; 
 int FORCE_MODE_SPD ; 
 int FORCE_MODE_TX_FC ; 
 int FORCE_RX_FC ; 
 int FORCE_SPD_S ; 
 int FORCE_TX_FC ; 
 int IPG_96BIT_WITH_SHORT_IPG ; 
 int IPG_CFG_S ; 
 int MAC_MODE ; 
 int MAC_RX_EN ; 
 int MAC_SPD_1000 ; 
 scalar_t__ MAC_SPD_2500 ; 
 int MAC_TX_EN ; 
 int MT753X_NUM_PORTS ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int /*<<< orphan*/  PMCR (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mt7531_set_port_rgmii (struct gsw_mt753x*,int) ; 
 int /*<<< orphan*/  mt7531_set_port_sgmii_an_mode (struct gsw_mt753x*,int,struct mt753x_port_cfg*) ; 
 int /*<<< orphan*/  mt7531_set_port_sgmii_force_mode (struct gsw_mt753x*,int,struct mt753x_port_cfg*) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_modes (int) ; 

__attribute__((used)) static int mt7531_mac_port_setup(struct gsw_mt753x *gsw, u32 port,
				 struct mt753x_port_cfg *port_cfg)
{
	u32 pmcr;
	u32 speed;

	if (port < 5 || port >= MT753X_NUM_PORTS) {
		dev_info(gsw->dev, "port %d is not a MAC port\n", port);
		return -EINVAL;
	}

	if (port_cfg->enabled) {
		pmcr = (IPG_96BIT_WITH_SHORT_IPG << IPG_CFG_S) |
		       MAC_MODE | MAC_TX_EN | MAC_RX_EN |
		       BKOFF_EN | BACKPR_EN;

		if (port_cfg->force_link) {
			/* PMCR's speed field 0x11 is reserved,
			 * sw should set 0x10
			 */
			speed = port_cfg->speed;
			if (port_cfg->speed == MAC_SPD_2500)
				speed = MAC_SPD_1000;

			pmcr |= FORCE_MODE_LNK | FORCE_LINK |
				FORCE_MODE_SPD | FORCE_MODE_DPX |
				FORCE_MODE_RX_FC | FORCE_MODE_TX_FC |
				FORCE_RX_FC | FORCE_TX_FC |
				(speed << FORCE_SPD_S);

			if (port_cfg->duplex)
				pmcr |= FORCE_DPX;
		}
	} else {
		pmcr = FORCE_MODE_LNK;
	}

	switch (port_cfg->phy_mode) {
	case PHY_INTERFACE_MODE_RGMII:
		mt7531_set_port_rgmii(gsw, port);
		break;
	case PHY_INTERFACE_MODE_SGMII:
		if (port_cfg->force_link)
			mt7531_set_port_sgmii_force_mode(gsw, port, port_cfg);
		else
			mt7531_set_port_sgmii_an_mode(gsw, port, port_cfg);
		break;
	default:
		if (port_cfg->enabled)
			dev_info(gsw->dev, "%s is not supported by port %d\n",
				 phy_modes(port_cfg->phy_mode), port);

		pmcr = FORCE_MODE_LNK;
	}

	mt753x_reg_write(gsw, PMCR(port), pmcr);

	return 0;
}