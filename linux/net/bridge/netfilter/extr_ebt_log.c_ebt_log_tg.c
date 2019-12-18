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
struct xt_action_param {struct ebt_log_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int logflags; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ log; } ;
struct nf_loginfo {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct net {int dummy; } ;
struct ebt_log_info {int bitmask; int /*<<< orphan*/  prefix; int /*<<< orphan*/  loglevel; } ;

/* Variables and functions */
 unsigned int EBT_CONTINUE ; 
 int EBT_LOG_NFLOG ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 int /*<<< orphan*/  ebt_log_packet (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_loginfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_packet (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_loginfo*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_hooknum (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param const*) ; 
 struct net* xt_net (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_out (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
ebt_log_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ebt_log_info *info = par->targinfo;
	struct nf_loginfo li;
	struct net *net = xt_net(par);

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = info->loglevel;
	li.u.log.logflags = info->bitmask;

	/* Remember that we have to use ebt_log_packet() not to break backward
	 * compatibility. We cannot use the default bridge packet logger via
	 * nf_log_packet() with NFT_LOG_TYPE_LOG here. --Pablo
	 */
	if (info->bitmask & EBT_LOG_NFLOG)
		nf_log_packet(net, NFPROTO_BRIDGE, xt_hooknum(par), skb,
			      xt_in(par), xt_out(par), &li, "%s",
			      info->prefix);
	else
		ebt_log_packet(net, NFPROTO_BRIDGE, xt_hooknum(par), skb,
			       xt_in(par), xt_out(par), &li, info->prefix);
	return EBT_CONTINUE;
}