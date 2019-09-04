#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dpni_taildrop {int enable; int /*<<< orphan*/  threshold; } ;
struct dpni_queue_id {int /*<<< orphan*/  fqid; } ;
struct TYPE_8__ {int priority; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct dpni_queue {scalar_t__ user_context; TYPE_4__ destination; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; TYPE_2__* net_dev; } ;
struct dpaa2_eth_fq {int /*<<< orphan*/  flowid; TYPE_3__* channel; int /*<<< orphan*/  fqid; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dpcon_id; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_TAILDROP_THRESH ; 
 int /*<<< orphan*/  DPNI_CP_QUEUE ; 
 int /*<<< orphan*/  DPNI_DEST_DPCON ; 
 int DPNI_QUEUE_OPT_DEST ; 
 int DPNI_QUEUE_OPT_USER_CTX ; 
 int /*<<< orphan*/  DPNI_QUEUE_RX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dpni_get_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_queue*,struct dpni_queue_id*) ; 
 int dpni_set_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dpni_queue*) ; 
 int dpni_set_taildrop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_taildrop*) ; 

__attribute__((used)) static int setup_rx_flow(struct dpaa2_eth_priv *priv,
			 struct dpaa2_eth_fq *fq)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct dpni_queue queue;
	struct dpni_queue_id qid;
	struct dpni_taildrop td;
	int err;

	err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, 0, fq->flowid, &queue, &qid);
	if (err) {
		dev_err(dev, "dpni_get_queue(RX) failed\n");
		return err;
	}

	fq->fqid = qid.fqid;

	queue.destination.id = fq->channel->dpcon_id;
	queue.destination.type = DPNI_DEST_DPCON;
	queue.destination.priority = 1;
	queue.user_context = (u64)(uintptr_t)fq;
	err = dpni_set_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, 0, fq->flowid,
			     DPNI_QUEUE_OPT_USER_CTX | DPNI_QUEUE_OPT_DEST,
			     &queue);
	if (err) {
		dev_err(dev, "dpni_set_queue(RX) failed\n");
		return err;
	}

	td.enable = 1;
	td.threshold = DPAA2_ETH_TAILDROP_THRESH;
	err = dpni_set_taildrop(priv->mc_io, 0, priv->mc_token, DPNI_CP_QUEUE,
				DPNI_QUEUE_RX, 0, fq->flowid, &td);
	if (err) {
		dev_err(dev, "dpni_set_threshold() failed\n");
		return err;
	}

	return 0;
}