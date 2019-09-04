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
struct veth_priv {TYPE_1__* rq; } ;
struct net_device {int num_rx_queues; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int veth_alloc_queues(struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	int i;

	priv->rq = kcalloc(dev->num_rx_queues, sizeof(*priv->rq), GFP_KERNEL);
	if (!priv->rq)
		return -ENOMEM;

	for (i = 0; i < dev->num_rx_queues; i++)
		priv->rq[i].dev = dev;

	return 0;
}