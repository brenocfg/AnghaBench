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
struct xt_hmark_info {int flags; } ;
struct xt_action_param {struct xt_hmark_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct hmark_tuple {int dummy; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  XT_HMARK_CT ; 
 int XT_HMARK_FLAG (int /*<<< orphan*/ ) ; 
 scalar_t__ hmark_ct_set_htuple (struct sk_buff*,struct hmark_tuple*,struct xt_hmark_info const*) ; 
 int /*<<< orphan*/  hmark_hash (struct hmark_tuple*,struct xt_hmark_info const*) ; 
 scalar_t__ hmark_pkt_set_htuple_ipv4 (struct sk_buff*,struct hmark_tuple*,struct xt_hmark_info const*) ; 
 int /*<<< orphan*/  memset (struct hmark_tuple*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
hmark_tg_v4(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_hmark_info *info = par->targinfo;
	struct hmark_tuple t;

	memset(&t, 0, sizeof(struct hmark_tuple));

	if (info->flags & XT_HMARK_FLAG(XT_HMARK_CT)) {
		if (hmark_ct_set_htuple(skb, &t, info) < 0)
			return XT_CONTINUE;
	} else {
		if (hmark_pkt_set_htuple_ipv4(skb, &t, info) < 0)
			return XT_CONTINUE;
	}

	skb->mark = hmark_hash(&t, info);
	return XT_CONTINUE;
}