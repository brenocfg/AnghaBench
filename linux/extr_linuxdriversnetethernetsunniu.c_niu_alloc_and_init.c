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
typedef  int /*<<< orphan*/  u8 ;
struct platform_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct niu_ops {int dummy; } ;
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_enable; struct niu_ops const* ops; struct device* device; struct platform_device* op; struct pci_dev* pdev; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIU_NUM_TXCHAN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  niu_debug ; 
 int /*<<< orphan*/  niu_reset_task ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device *niu_alloc_and_init(struct device *gen_dev,
					     struct pci_dev *pdev,
					     struct platform_device *op,
					     const struct niu_ops *ops, u8 port)
{
	struct net_device *dev;
	struct niu *np;

	dev = alloc_etherdev_mq(sizeof(struct niu), NIU_NUM_TXCHAN);
	if (!dev)
		return NULL;

	SET_NETDEV_DEV(dev, gen_dev);

	np = netdev_priv(dev);
	np->dev = dev;
	np->pdev = pdev;
	np->op = op;
	np->device = gen_dev;
	np->ops = ops;

	np->msg_enable = niu_debug;

	spin_lock_init(&np->lock);
	INIT_WORK(&np->reset_task, niu_reset_task);

	np->port = port;

	return dev;
}