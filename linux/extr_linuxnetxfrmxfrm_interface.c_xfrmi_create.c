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
struct xfrm_if_parms {int /*<<< orphan*/  link; scalar_t__* name; } ;
struct xfrm_if {int /*<<< orphan*/  phydev; struct net_device* dev; struct net* net; struct xfrm_if_parms p; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 struct xfrm_if* ERR_PTR (int) ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__*,int) ; 
 int xfrmi_create2 (struct net_device*) ; 
 int /*<<< orphan*/  xfrmi_dev_setup ; 

__attribute__((used)) static struct xfrm_if *xfrmi_create(struct net *net, struct xfrm_if_parms *p)
{
	struct net_device *dev;
	struct xfrm_if *xi;
	char name[IFNAMSIZ];
	int err;

	if (p->name[0]) {
		strlcpy(name, p->name, IFNAMSIZ);
	} else {
		err = -EINVAL;
		goto failed;
	}

	dev = alloc_netdev(sizeof(*xi), name, NET_NAME_UNKNOWN, xfrmi_dev_setup);
	if (!dev) {
		err = -EAGAIN;
		goto failed;
	}

	dev_net_set(dev, net);

	xi = netdev_priv(dev);
	xi->p = *p;
	xi->net = net;
	xi->dev = dev;
	xi->phydev = dev_get_by_index(net, p->link);
	if (!xi->phydev) {
		err = -ENODEV;
		goto failed_free;
	}

	err = xfrmi_create2(dev);
	if (err < 0)
		goto failed_dev_put;

	return xi;

failed_dev_put:
	dev_put(xi->phydev);
failed_free:
	free_netdev(dev);
failed:
	return ERR_PTR(err);
}