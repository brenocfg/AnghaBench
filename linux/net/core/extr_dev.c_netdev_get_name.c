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
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int /*<<< orphan*/  devnet_rename_seq ; 
 unsigned int raw_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int netdev_get_name(struct net *net, char *name, int ifindex)
{
	struct net_device *dev;
	unsigned int seq;

retry:
	seq = raw_seqcount_begin(&devnet_rename_seq);
	rcu_read_lock();
	dev = dev_get_by_index_rcu(net, ifindex);
	if (!dev) {
		rcu_read_unlock();
		return -ENODEV;
	}

	strcpy(name, dev->name);
	rcu_read_unlock();
	if (read_seqcount_retry(&devnet_rename_seq, seq)) {
		cond_resched();
		goto retry;
	}

	return 0;
}