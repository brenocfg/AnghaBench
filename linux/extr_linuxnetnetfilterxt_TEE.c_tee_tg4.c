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
struct TYPE_4__ {int /*<<< orphan*/  in; } ;
struct xt_tee_tginfo {TYPE_2__ gw; TYPE_1__* priv; } ;
struct xt_action_param {struct xt_tee_tginfo* targinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int oif; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  nf_dup_ipv4 (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xt_hooknum (struct xt_action_param const*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
tee_tg4(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_tee_tginfo *info = par->targinfo;
	int oif = info->priv ? info->priv->oif : 0;

	nf_dup_ipv4(xt_net(par), skb, xt_hooknum(par), &info->gw.in, oif);

	return XT_CONTINUE;
}