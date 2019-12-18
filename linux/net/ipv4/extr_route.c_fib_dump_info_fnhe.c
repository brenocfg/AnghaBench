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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct netlink_callback {TYPE_1__* skb; } ;
struct net {int dummy; } ;
struct fnhe_hash_bucket {int dummy; } ;
struct fib_nh_common {int nhc_flags; int /*<<< orphan*/  nhc_exceptions; } ;
struct fib_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int RTNH_F_DEAD ; 
 struct fib_nh_common* fib_info_nhc (struct fib_info*,int) ; 
 int fib_info_num_path (struct fib_info*) ; 
 int fnhe_dump_bucket (struct net*,struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct fnhe_hash_bucket*,int,int*,int,unsigned int) ; 
 int fnhe_genid (struct net*) ; 
 struct fnhe_hash_bucket* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int fib_dump_info_fnhe(struct sk_buff *skb, struct netlink_callback *cb,
		       u32 table_id, struct fib_info *fi,
		       int *fa_index, int fa_start, unsigned int flags)
{
	struct net *net = sock_net(cb->skb->sk);
	int nhsel, genid = fnhe_genid(net);

	for (nhsel = 0; nhsel < fib_info_num_path(fi); nhsel++) {
		struct fib_nh_common *nhc = fib_info_nhc(fi, nhsel);
		struct fnhe_hash_bucket *bucket;
		int err;

		if (nhc->nhc_flags & RTNH_F_DEAD)
			continue;

		rcu_read_lock();
		bucket = rcu_dereference(nhc->nhc_exceptions);
		err = 0;
		if (bucket)
			err = fnhe_dump_bucket(net, skb, cb, table_id, bucket,
					       genid, fa_index, fa_start,
					       flags);
		rcu_read_unlock();
		if (err)
			return err;
	}

	return 0;
}