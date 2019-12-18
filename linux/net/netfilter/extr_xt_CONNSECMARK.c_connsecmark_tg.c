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
struct xt_connsecmark_target_info {int mode; } ;
struct xt_action_param {struct xt_connsecmark_target_info* targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CONNSECMARK_RESTORE 129 
#define  CONNSECMARK_SAVE 128 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  secmark_restore (struct sk_buff*) ; 
 int /*<<< orphan*/  secmark_save (struct sk_buff*) ; 

__attribute__((used)) static unsigned int
connsecmark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_connsecmark_target_info *info = par->targinfo;

	switch (info->mode) {
	case CONNSECMARK_SAVE:
		secmark_save(skb);
		break;

	case CONNSECMARK_RESTORE:
		secmark_restore(skb);
		break;

	default:
		BUG();
	}

	return XT_CONTINUE;
}