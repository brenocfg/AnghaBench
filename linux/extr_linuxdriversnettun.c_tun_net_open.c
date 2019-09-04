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
struct tun_struct {int numqueues; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_3__ {TYPE_2__* sk; } ;
struct tun_file {TYPE_1__ socket; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sk_write_space ) (TYPE_2__*) ;} ;

/* Variables and functions */
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 struct tun_file* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int tun_net_open(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);
	int i;

	netif_tx_start_all_queues(dev);

	for (i = 0; i < tun->numqueues; i++) {
		struct tun_file *tfile;

		tfile = rtnl_dereference(tun->tfiles[i]);
		tfile->socket.sk->sk_write_space(tfile->socket.sk);
	}

	return 0;
}