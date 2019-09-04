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
struct xlr_net_priv {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  port_id; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int BYTE_OFFSET ; 
 int O_DESC_PACK_CTRL__BYTEOFFSET ; 
 int O_DESC_PACK_CTRL__MAXENTRY ; 
 int O_DESC_PACK_CTRL__REGULARSIZE ; 
 int O_INTMASK__ABORT ; 
 int O_INTMASK__MDINT ; 
 int O_INTMASK__P2PSPILLECC ; 
 int O_INTMASK__TAGFULL ; 
 int O_INTMASK__TXFETCHERROR ; 
 int O_INTMASK__TXILLEGAL ; 
 int O_INTMASK__UNDERRUN ; 
 int O_STATCTRL__CLRCNT ; 
 int /*<<< orphan*/  R_CORECONTROL ; 
 int /*<<< orphan*/  R_DESC_PACK_CTRL ; 
 int /*<<< orphan*/  R_INTMASK ; 
 int /*<<< orphan*/  R_MAC_CONFIG_2 ; 
 int /*<<< orphan*/  R_STATCTRL ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_nae_wreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xlr_port_disable (struct xlr_net_priv*) ; 
 int /*<<< orphan*/  xlr_port_enable (struct xlr_net_priv*) ; 
 int /*<<< orphan*/  xlr_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int xlr_setup_mdio (struct xlr_net_priv*,struct platform_device*) ; 

__attribute__((used)) static int xlr_gmac_init(struct xlr_net_priv *priv,
			 struct platform_device *pdev)
{
	int ret;

	pr_info("Initializing the gmac%d\n", priv->port_id);

	xlr_port_disable(priv);

	xlr_nae_wreg(priv->base_addr, R_DESC_PACK_CTRL,
		     (1 << O_DESC_PACK_CTRL__MAXENTRY) |
		     (BYTE_OFFSET << O_DESC_PACK_CTRL__BYTEOFFSET) |
		     (1600 << O_DESC_PACK_CTRL__REGULARSIZE));

	ret = xlr_setup_mdio(priv, pdev);
	if (ret)
		return ret;
	xlr_port_enable(priv);

	/* Enable Full-duplex/1000Mbps/CRC */
	xlr_nae_wreg(priv->base_addr, R_MAC_CONFIG_2, 0x7217);
	/* speed 2.5Mhz */
	xlr_nae_wreg(priv->base_addr, R_CORECONTROL, 0x02);
	/* Setup Interrupt mask reg */
	xlr_nae_wreg(priv->base_addr, R_INTMASK, (1 << O_INTMASK__TXILLEGAL) |
		     (1 << O_INTMASK__MDINT) | (1 << O_INTMASK__TXFETCHERROR) |
		     (1 << O_INTMASK__P2PSPILLECC) | (1 << O_INTMASK__TAGFULL) |
		     (1 << O_INTMASK__UNDERRUN) | (1 << O_INTMASK__ABORT));

	/* Clear all stats */
	xlr_reg_update(priv->base_addr, R_STATCTRL, 0, 1 << O_STATCTRL__CLRCNT);
	xlr_reg_update(priv->base_addr, R_STATCTRL, 1 << 2, 1 << 2);
	return 0;
}