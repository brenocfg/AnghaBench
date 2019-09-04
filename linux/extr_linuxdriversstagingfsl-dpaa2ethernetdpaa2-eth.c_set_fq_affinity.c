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
struct dpaa2_eth_priv {int num_fqs; int /*<<< orphan*/  dpio_cpumask; TYPE_2__* net_dev; struct dpaa2_eth_fq* fq; } ;
struct dpaa2_eth_fq {int type; int target_cpu; int /*<<< orphan*/  channel; int /*<<< orphan*/  flowid; } ;
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
#define  DPAA2_RX_FQ 129 
#define  DPAA2_TX_CONF_FQ 128 
 int /*<<< orphan*/  cpumask_clear (struct cpumask*) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int cpumask_next (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  get_affine_channel (struct dpaa2_eth_priv*,int) ; 
 int netif_set_xps_queue (TYPE_2__*,struct cpumask*,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 

__attribute__((used)) static void set_fq_affinity(struct dpaa2_eth_priv *priv)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct cpumask xps_mask;
	struct dpaa2_eth_fq *fq;
	int rx_cpu, txc_cpu;
	int i, err;

	/* For each FQ, pick one channel/CPU to deliver frames to.
	 * This may well change at runtime, either through irqbalance or
	 * through direct user intervention.
	 */
	rx_cpu = txc_cpu = cpumask_first(&priv->dpio_cpumask);

	for (i = 0; i < priv->num_fqs; i++) {
		fq = &priv->fq[i];
		switch (fq->type) {
		case DPAA2_RX_FQ:
			fq->target_cpu = rx_cpu;
			rx_cpu = cpumask_next(rx_cpu, &priv->dpio_cpumask);
			if (rx_cpu >= nr_cpu_ids)
				rx_cpu = cpumask_first(&priv->dpio_cpumask);
			break;
		case DPAA2_TX_CONF_FQ:
			fq->target_cpu = txc_cpu;

			/* Tell the stack to affine to txc_cpu the Tx queue
			 * associated with the confirmation one
			 */
			cpumask_clear(&xps_mask);
			cpumask_set_cpu(txc_cpu, &xps_mask);
			err = netif_set_xps_queue(priv->net_dev, &xps_mask,
						  fq->flowid);
			if (err)
				dev_err(dev, "Error setting XPS queue\n");

			txc_cpu = cpumask_next(txc_cpu, &priv->dpio_cpumask);
			if (txc_cpu >= nr_cpu_ids)
				txc_cpu = cpumask_first(&priv->dpio_cpumask);
			break;
		default:
			dev_err(dev, "Unknown FQ type: %d\n", fq->type);
		}
		fq->channel = get_affine_channel(priv, fq->target_cpu);
	}
}