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
struct xt_classify_target_info {int /*<<< orphan*/  priority; } ;
struct xt_action_param {struct xt_classify_target_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 

__attribute__((used)) static unsigned int
classify_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_classify_target_info *clinfo = par->targinfo;

	skb->priority = clinfo->priority;
	return XT_CONTINUE;
}