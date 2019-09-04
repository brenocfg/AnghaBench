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
struct sk_buff {int dummy; } ;
struct seg6_pernet_data {int /*<<< orphan*/  lock; struct in6_addr* tun_src; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t SEG6_ATTR_DST ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  kfree (struct in6_addr*) ; 
 struct in6_addr* kmemdup (struct in6_addr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct in6_addr* nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct in6_addr*,struct in6_addr*) ; 
 struct seg6_pernet_data* seg6_pernet (struct net*) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static int seg6_genl_set_tunsrc(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct in6_addr *val, *t_old, *t_new;
	struct seg6_pernet_data *sdata;

	sdata = seg6_pernet(net);

	if (!info->attrs[SEG6_ATTR_DST])
		return -EINVAL;

	val = nla_data(info->attrs[SEG6_ATTR_DST]);
	t_new = kmemdup(val, sizeof(*val), GFP_KERNEL);
	if (!t_new)
		return -ENOMEM;

	mutex_lock(&sdata->lock);

	t_old = sdata->tun_src;
	rcu_assign_pointer(sdata->tun_src, t_new);

	mutex_unlock(&sdata->lock);

	synchronize_net();
	kfree(t_old);

	return 0;
}