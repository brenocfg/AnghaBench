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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;
struct TYPE_2__ {int /*<<< orphan*/  tun_src; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  SEG6_ATTR_DST ; 
 int /*<<< orphan*/  SEG6_CMD_GET_TUNSRC ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct in6_addr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct in6_addr* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seg6_genl_family ; 
 TYPE_1__* seg6_pernet (struct net*) ; 

__attribute__((used)) static int seg6_genl_get_tunsrc(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct in6_addr *tun_src;
	struct sk_buff *msg;
	void *hdr;

	msg = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &seg6_genl_family, 0, SEG6_CMD_GET_TUNSRC);
	if (!hdr)
		goto free_msg;

	rcu_read_lock();
	tun_src = rcu_dereference(seg6_pernet(net)->tun_src);

	if (nla_put(msg, SEG6_ATTR_DST, sizeof(struct in6_addr), tun_src))
		goto nla_put_failure;

	rcu_read_unlock();

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

nla_put_failure:
	rcu_read_unlock();
free_msg:
	nlmsg_free(msg);
	return -ENOMEM;
}