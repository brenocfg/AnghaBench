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
struct tx_device_buffer {int /*<<< orphan*/  skb; int /*<<< orphan*/  (* complete_handler ) (struct ks_wlan_private*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sendp; } ;
struct TYPE_2__ {size_t qhead; struct tx_device_buffer* tx_dev_buff; } ;
struct ks_wlan_private {int /*<<< orphan*/  rx_bh_task; TYPE_1__ tx_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  inc_txqhead (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ txq_has_space (struct ks_wlan_private*) ; 

__attribute__((used)) static void trx_device_exit(struct ks_wlan_private *priv)
{
	struct tx_device_buffer *sp;

	/* tx buffer clear */
	while (txq_has_space(priv)) {
		sp = &priv->tx_dev.tx_dev_buff[priv->tx_dev.qhead];
		kfree(sp->sendp);
		if (sp->complete_handler)	/* TX Complete */
			(*sp->complete_handler)(priv, sp->skb);
		inc_txqhead(priv);
	}

	tasklet_kill(&priv->rx_bh_task);
}