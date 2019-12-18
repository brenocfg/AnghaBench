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
typedef  int /*<<< orphan*/  u32 ;
struct xt_secmark_target_info {int /*<<< orphan*/  secid; } ;
struct xt_action_param {struct xt_secmark_target_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  secmark; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SECMARK_MODE_SEL 128 
 unsigned int XT_CONTINUE ; 
 int mode ; 

__attribute__((used)) static unsigned int
secmark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	u32 secmark = 0;
	const struct xt_secmark_target_info *info = par->targinfo;

	switch (mode) {
	case SECMARK_MODE_SEL:
		secmark = info->secid;
		break;
	default:
		BUG();
	}

	skb->secmark = secmark;
	return XT_CONTINUE;
}