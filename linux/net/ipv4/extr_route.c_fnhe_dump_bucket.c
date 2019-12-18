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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rtable {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct fnhe_hash_bucket {int /*<<< orphan*/  chain; } ;
struct fib_nh_exception {int fnhe_genid; int /*<<< orphan*/  fnhe_daddr; int /*<<< orphan*/  fnhe_rth_output; int /*<<< orphan*/  fnhe_rth_input; scalar_t__ fnhe_expires; int /*<<< orphan*/  fnhe_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int FNHE_HASH_SIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int rt_fill_info (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtable*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fnhe_dump_bucket(struct net *net, struct sk_buff *skb,
			    struct netlink_callback *cb, u32 table_id,
			    struct fnhe_hash_bucket *bucket, int genid,
			    int *fa_index, int fa_start, unsigned int flags)
{
	int i;

	for (i = 0; i < FNHE_HASH_SIZE; i++) {
		struct fib_nh_exception *fnhe;

		for (fnhe = rcu_dereference(bucket[i].chain); fnhe;
		     fnhe = rcu_dereference(fnhe->fnhe_next)) {
			struct rtable *rt;
			int err;

			if (*fa_index < fa_start)
				goto next;

			if (fnhe->fnhe_genid != genid)
				goto next;

			if (fnhe->fnhe_expires &&
			    time_after(jiffies, fnhe->fnhe_expires))
				goto next;

			rt = rcu_dereference(fnhe->fnhe_rth_input);
			if (!rt)
				rt = rcu_dereference(fnhe->fnhe_rth_output);
			if (!rt)
				goto next;

			err = rt_fill_info(net, fnhe->fnhe_daddr, 0, rt,
					   table_id, NULL, skb,
					   NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, flags);
			if (err)
				return err;
next:
			(*fa_index)++;
		}
	}

	return 0;
}