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
struct bdx_priv {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int MAC_LINK_STAT ; 
 int READ_REG (struct bdx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regMAC_LNK_STAT ; 

__attribute__((used)) static void bdx_link_changed(struct bdx_priv *priv)
{
	u32 link = READ_REG(priv, regMAC_LNK_STAT) & MAC_LINK_STAT;

	if (!link) {
		if (netif_carrier_ok(priv->ndev)) {
			netif_stop_queue(priv->ndev);
			netif_carrier_off(priv->ndev);
			netdev_err(priv->ndev, "Link Down\n");
		}
	} else {
		if (!netif_carrier_ok(priv->ndev)) {
			netif_wake_queue(priv->ndev);
			netif_carrier_on(priv->ndev);
			netdev_err(priv->ndev, "Link Up\n");
		}
	}
}