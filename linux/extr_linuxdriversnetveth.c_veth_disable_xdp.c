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
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;
struct veth_rq {TYPE_1__ xdp_rxq; int /*<<< orphan*/  xdp_mem; int /*<<< orphan*/  xdp_prog; } ;
struct veth_priv {struct veth_rq* rq; } ;
struct net_device {int real_num_rx_queues; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  veth_napi_del (struct net_device*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (TYPE_1__*) ; 

__attribute__((used)) static void veth_disable_xdp(struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < dev->real_num_rx_queues; i++)
		rcu_assign_pointer(priv->rq[i].xdp_prog, NULL);
	veth_napi_del(dev);
	for (i = 0; i < dev->real_num_rx_queues; i++) {
		struct veth_rq *rq = &priv->rq[i];

		rq->xdp_rxq.mem = rq->xdp_mem;
		xdp_rxq_info_unreg(&rq->xdp_rxq);
	}
}