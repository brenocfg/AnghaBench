#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnt_tx_desc {int dummy; } ;
struct vnt_rx_desc {int dummy; } ;
struct TYPE_4__ {int rx_descs0; int rx_descs1; int* tx_descs; } ;
struct vnt_private {int /*<<< orphan*/  tx_bufs_dma0; scalar_t__ tx0_bufs; TYPE_2__ opts; TYPE_1__* pcid; int /*<<< orphan*/  pool_dma; scalar_t__ aRD0Ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CB_BEACON_BUF_SIZE ; 
 int CB_MAX_BUF_SIZE ; 
 int PKT_BUF_SZ ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_free_rings(struct vnt_private *priv)
{
	dma_free_coherent(&priv->pcid->dev,
			  priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc) +
			  priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc) +
			  priv->opts.tx_descs[0] * sizeof(struct vnt_tx_desc) +
			  priv->opts.tx_descs[1] * sizeof(struct vnt_tx_desc),
			  priv->aRD0Ring, priv->pool_dma);

	if (priv->tx0_bufs)
		dma_free_coherent(&priv->pcid->dev,
				  priv->opts.tx_descs[0] * PKT_BUF_SZ +
				  priv->opts.tx_descs[1] * PKT_BUF_SZ +
				  CB_BEACON_BUF_SIZE +
				  CB_MAX_BUF_SIZE,
				  priv->tx0_bufs, priv->tx_bufs_dma0);
}