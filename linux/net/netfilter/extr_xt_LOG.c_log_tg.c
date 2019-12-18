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
struct xt_log_info {int /*<<< orphan*/  prefix; int /*<<< orphan*/  logflags; int /*<<< orphan*/  level; } ;
struct xt_action_param {struct xt_log_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  logflags; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ log; } ;
struct nf_loginfo {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  nf_log_packet (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_loginfo*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_hooknum (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param const*) ; 
 struct net* xt_net (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_out (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
log_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_log_info *loginfo = par->targinfo;
	struct net *net = xt_net(par);
	struct nf_loginfo li;

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = loginfo->level;
	li.u.log.logflags = loginfo->logflags;

	nf_log_packet(net, xt_family(par), xt_hooknum(par), skb, xt_in(par),
		      xt_out(par), &li, "%s", loginfo->prefix);
	return XT_CONTINUE;
}