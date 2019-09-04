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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_stop_tx (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_stop_tx_dma(struct stmmac_priv *priv, u32 chan)
{
	netdev_dbg(priv->dev, "DMA TX processes stopped in channel %d\n", chan);
	stmmac_stop_tx(priv, priv->ioaddr, chan);
}