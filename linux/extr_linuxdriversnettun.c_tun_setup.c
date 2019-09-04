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
struct tun_struct {int /*<<< orphan*/  link_ksettings; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; } ;
struct net_device {int needs_free_netdev; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int /*<<< orphan*/  TUN_READQ_SIZE ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tun_default_link_ksettings (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_ethtool_ops ; 
 int /*<<< orphan*/  tun_free_netdev ; 

__attribute__((used)) static void tun_setup(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	tun->owner = INVALID_UID;
	tun->group = INVALID_GID;
	tun_default_link_ksettings(dev, &tun->link_ksettings);

	dev->ethtool_ops = &tun_ethtool_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = tun_free_netdev;
	/* We prefer our own queue length */
	dev->tx_queue_len = TUN_READQ_SIZE;
}