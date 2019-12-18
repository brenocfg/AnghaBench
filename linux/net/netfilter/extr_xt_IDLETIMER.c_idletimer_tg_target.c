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
struct xt_action_param {struct idletimer_tg_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct idletimer_tg_info {int timeout; TYPE_1__* timer; int /*<<< orphan*/  label; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int idletimer_tg_target(struct sk_buff *skb,
					 const struct xt_action_param *par)
{
	const struct idletimer_tg_info *info = par->targinfo;

	pr_debug("resetting timer %s, timeout period %u\n",
		 info->label, info->timeout);

	mod_timer(&info->timer->timer,
		  msecs_to_jiffies(info->timeout * 1000) + jiffies);

	return XT_CONTINUE;
}