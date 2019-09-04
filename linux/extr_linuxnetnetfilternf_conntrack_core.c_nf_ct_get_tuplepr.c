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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_l4proto (struct sk_buff const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nf_ct_get_tuple (struct sk_buff const*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct nf_conntrack_tuple*,struct nf_conntrack_l4proto const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool nf_ct_get_tuplepr(const struct sk_buff *skb, unsigned int nhoff,
		       u_int16_t l3num,
		       struct net *net, struct nf_conntrack_tuple *tuple)
{
	const struct nf_conntrack_l4proto *l4proto;
	u8 protonum;
	int protoff;
	int ret;

	rcu_read_lock();

	protoff = get_l4proto(skb, nhoff, l3num, &protonum);
	if (protoff <= 0) {
		rcu_read_unlock();
		return false;
	}

	l4proto = __nf_ct_l4proto_find(l3num, protonum);

	ret = nf_ct_get_tuple(skb, nhoff, protoff, l3num, protonum, net, tuple,
			      l4proto);

	rcu_read_unlock();
	return ret;
}