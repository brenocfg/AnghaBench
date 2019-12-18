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
struct xt_ct_target_info {struct nf_conn* ct; } ;
struct xt_action_param {struct xt_ct_target_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 unsigned int xt_ct_target (struct sk_buff*,struct nf_conn*) ; 

__attribute__((used)) static unsigned int xt_ct_target_v0(struct sk_buff *skb,
				    const struct xt_action_param *par)
{
	const struct xt_ct_target_info *info = par->targinfo;
	struct nf_conn *ct = info->ct;

	return xt_ct_target(skb, ct);
}