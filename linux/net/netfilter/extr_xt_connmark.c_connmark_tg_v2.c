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
struct xt_connmark_tginfo2 {int dummy; } ;
struct xt_action_param {struct xt_connmark_tginfo2* targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int connmark_tg_shift (struct sk_buff*,struct xt_connmark_tginfo2 const*) ; 

__attribute__((used)) static unsigned int
connmark_tg_v2(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_connmark_tginfo2 *info = par->targinfo;

	return connmark_tg_shift(skb, info);
}