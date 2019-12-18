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
struct ila_xlat_params {int dummy; } ;
struct ila_net {int dummy; } ;
struct ila_map {int dummy; } ;
struct genl_info {TYPE_1__* genlhdr; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int ila_dump_info (struct ila_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ila_map* ila_lookup_by_params (struct ila_xlat_params*,struct ila_net*) ; 
 int /*<<< orphan*/  ila_net_id ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_nl_config (struct genl_info*,struct ila_xlat_params*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int ila_xlat_nl_cmd_get_mapping(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct sk_buff *msg;
	struct ila_xlat_params xp;
	struct ila_map *ila;
	int ret;

	ret = parse_nl_config(info, &xp);
	if (ret)
		return ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	rcu_read_lock();

	ila = ila_lookup_by_params(&xp, ilan);
	if (ila) {
		ret = ila_dump_info(ila,
				    info->snd_portid,
				    info->snd_seq, 0, msg,
				    info->genlhdr->cmd);
	}

	rcu_read_unlock();

	if (ret < 0)
		goto out_free;

	return genlmsg_reply(msg, info);

out_free:
	nlmsg_free(msg);
	return ret;
}