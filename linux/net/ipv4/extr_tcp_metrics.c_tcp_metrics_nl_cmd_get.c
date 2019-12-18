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
struct tcp_metrics_block {int /*<<< orphan*/  tcpm_saddr; int /*<<< orphan*/  tcpm_daddr; int /*<<< orphan*/  tcpm_next; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct inetpeer_addr {int dummy; } ;
struct genl_info {TYPE_1__* genlhdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 scalar_t__ addr_same (int /*<<< orphan*/ *,struct inetpeer_addr*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 unsigned int hash_32 (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 unsigned int net_hash_mix (struct net*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_nl_addr (struct genl_info*,struct inetpeer_addr*,unsigned int*,int /*<<< orphan*/ ) ; 
 int parse_nl_saddr (struct genl_info*,struct inetpeer_addr*) ; 
 struct tcp_metrics_block* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int tcp_metrics_fill_info (struct sk_buff*,struct tcp_metrics_block*) ; 
 TYPE_2__* tcp_metrics_hash ; 
 int /*<<< orphan*/  tcp_metrics_hash_log ; 
 int /*<<< orphan*/  tcp_metrics_nl_family ; 
 int /*<<< orphan*/  tm_net (struct tcp_metrics_block*) ; 

__attribute__((used)) static int tcp_metrics_nl_cmd_get(struct sk_buff *skb, struct genl_info *info)
{
	struct tcp_metrics_block *tm;
	struct inetpeer_addr saddr, daddr;
	unsigned int hash;
	struct sk_buff *msg;
	struct net *net = genl_info_net(info);
	void *reply;
	int ret;
	bool src = true;

	ret = parse_nl_addr(info, &daddr, &hash, 0);
	if (ret < 0)
		return ret;

	ret = parse_nl_saddr(info, &saddr);
	if (ret < 0)
		src = false;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &tcp_metrics_nl_family, 0,
				  info->genlhdr->cmd);
	if (!reply)
		goto nla_put_failure;

	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metrics_hash_log);
	ret = -ESRCH;
	rcu_read_lock();
	for (tm = rcu_dereference(tcp_metrics_hash[hash].chain); tm;
	     tm = rcu_dereference(tm->tcpm_next)) {
		if (addr_same(&tm->tcpm_daddr, &daddr) &&
		    (!src || addr_same(&tm->tcpm_saddr, &saddr)) &&
		    net_eq(tm_net(tm), net)) {
			ret = tcp_metrics_fill_info(msg, tm);
			break;
		}
	}
	rcu_read_unlock();
	if (ret < 0)
		goto out_free;

	genlmsg_end(msg, reply);
	return genlmsg_reply(msg, info);

nla_put_failure:
	ret = -EMSGSIZE;

out_free:
	nlmsg_free(msg);
	return ret;
}