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
struct ppp_config {int unit; int ifname_is_set; struct file* file; } ;
struct TYPE_2__ {int index; } ;
struct ppp {TYPE_1__ file; } ;
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;
struct net {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NET_NAME_ENUM ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ppp* netdev_priv (struct net_device*) ; 
 int ppp_dev_configure (struct net*,struct net_device*,struct ppp_config*) ; 
 int /*<<< orphan*/  ppp_link_ops ; 
 int /*<<< orphan*/  ppp_setup ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int ppp_create_interface(struct net *net, struct file *file, int *unit)
{
	struct ppp_config conf = {
		.file = file,
		.unit = *unit,
		.ifname_is_set = false,
	};
	struct net_device *dev;
	struct ppp *ppp;
	int err;

	dev = alloc_netdev(sizeof(struct ppp), "", NET_NAME_ENUM, ppp_setup);
	if (!dev) {
		err = -ENOMEM;
		goto err;
	}
	dev_net_set(dev, net);
	dev->rtnl_link_ops = &ppp_link_ops;

	rtnl_lock();

	err = ppp_dev_configure(net, dev, &conf);
	if (err < 0)
		goto err_dev;
	ppp = netdev_priv(dev);
	*unit = ppp->file.index;

	rtnl_unlock();

	return 0;

err_dev:
	rtnl_unlock();
	free_netdev(dev);
err:
	return err;
}