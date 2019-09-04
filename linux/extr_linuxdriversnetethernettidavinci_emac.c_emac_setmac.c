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
typedef  scalar_t__ u32 ;
struct emac_priv {int rx_addr_type; TYPE_1__* ndev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ EMAC_MAX_TXRX_CHANNELS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  emac_set_type0addr (struct emac_priv*,scalar_t__,char*) ; 
 int /*<<< orphan*/  emac_set_type1addr (struct emac_priv*,scalar_t__,char*) ; 
 int /*<<< orphan*/  emac_set_type2addr (struct emac_priv*,scalar_t__,char*,scalar_t__,int) ; 
 scalar_t__ netif_msg_drv (struct emac_priv*) ; 

__attribute__((used)) static void emac_setmac(struct emac_priv *priv, u32 ch, char *mac_addr)
{
	struct device *emac_dev = &priv->ndev->dev;

	if (priv->rx_addr_type == 0) {
		emac_set_type0addr(priv, ch, mac_addr);
	} else if (priv->rx_addr_type == 1) {
		u32 cnt;
		for (cnt = 0; cnt < EMAC_MAX_TXRX_CHANNELS; cnt++)
			emac_set_type1addr(priv, ch, mac_addr);
	} else if (priv->rx_addr_type == 2) {
		emac_set_type2addr(priv, ch, mac_addr, ch, 1);
		emac_set_type0addr(priv, ch, mac_addr);
	} else {
		if (netif_msg_drv(priv))
			dev_err(emac_dev, "DaVinci EMAC: Wrong addressing\n");
	}
}