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
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct net_device* alloc_etherdev_mqs (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  devm_free_netdev ; 
 int /*<<< orphan*/  devres_add (struct device*,struct net_device**) ; 
 struct net_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct net_device**) ; 

struct net_device *devm_alloc_etherdev_mqs(struct device *dev, int sizeof_priv,
					   unsigned int txqs, unsigned int rxqs)
{
	struct net_device **dr;
	struct net_device *netdev;

	dr = devres_alloc(devm_free_netdev, sizeof(*dr), GFP_KERNEL);
	if (!dr)
		return NULL;

	netdev = alloc_etherdev_mqs(sizeof_priv, txqs, rxqs);
	if (!netdev) {
		devres_free(dr);
		return NULL;
	}

	*dr = netdev;
	devres_add(dev, dr);

	return netdev;
}