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
typedef  void* u16 ;
struct dpaa2_eth_priv {size_t num_fqs; TYPE_1__* fq; } ;
struct TYPE_2__ {void* flowid; int /*<<< orphan*/  consume; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_RX_FQ ; 
 int /*<<< orphan*/  DPAA2_TX_CONF_FQ ; 
 int dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpaa2_eth_rx ; 
 int /*<<< orphan*/  dpaa2_eth_tx_conf ; 
 int /*<<< orphan*/  set_fq_affinity (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static void setup_fqs(struct dpaa2_eth_priv *priv)
{
	int i;

	/* We have one TxConf FQ per Tx flow.
	 * The number of Tx and Rx queues is the same.
	 * Tx queues come first in the fq array.
	 */
	for (i = 0; i < dpaa2_eth_queue_count(priv); i++) {
		priv->fq[priv->num_fqs].type = DPAA2_TX_CONF_FQ;
		priv->fq[priv->num_fqs].consume = dpaa2_eth_tx_conf;
		priv->fq[priv->num_fqs++].flowid = (u16)i;
	}

	for (i = 0; i < dpaa2_eth_queue_count(priv); i++) {
		priv->fq[priv->num_fqs].type = DPAA2_RX_FQ;
		priv->fq[priv->num_fqs].consume = dpaa2_eth_rx;
		priv->fq[priv->num_fqs++].flowid = (u16)i;
	}

	/* For each FQ, decide on which core to process incoming frames */
	set_fq_affinity(priv);
}