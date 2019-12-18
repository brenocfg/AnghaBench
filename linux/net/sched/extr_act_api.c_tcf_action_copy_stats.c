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
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct tc_action {scalar_t__ type; TYPE_1__ tcfa_qstats; int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  tcfa_rate_est; int /*<<< orphan*/  tcfa_bstats_hw; int /*<<< orphan*/  cpu_bstats_hw; int /*<<< orphan*/  tcfa_bstats; int /*<<< orphan*/  cpu_bstats; int /*<<< orphan*/  tcfa_lock; } ;
struct sk_buff {int dummy; } ;
struct gnet_dump {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_ACT_PAD ; 
 int /*<<< orphan*/  TCA_ACT_STATS ; 
 scalar_t__ TCA_OLD_COMPAT ; 
 int /*<<< orphan*/  TCA_PAD ; 
 int /*<<< orphan*/  TCA_STATS ; 
 int /*<<< orphan*/  TCA_XSTATS ; 
 scalar_t__ gnet_stats_copy_basic (int /*<<< orphan*/ *,struct gnet_dump*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_basic_hw (int /*<<< orphan*/ *,struct gnet_dump*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_finish_copy (struct gnet_dump*) ; 
 int gnet_stats_start_copy (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gnet_dump*,int /*<<< orphan*/ ) ; 
 int gnet_stats_start_copy_compat (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gnet_dump*,int /*<<< orphan*/ ) ; 

int tcf_action_copy_stats(struct sk_buff *skb, struct tc_action *p,
			  int compat_mode)
{
	int err = 0;
	struct gnet_dump d;

	if (p == NULL)
		goto errout;

	/* compat_mode being true specifies a call that is supposed
	 * to add additional backward compatibility statistic TLVs.
	 */
	if (compat_mode) {
		if (p->type == TCA_OLD_COMPAT)
			err = gnet_stats_start_copy_compat(skb, 0,
							   TCA_STATS,
							   TCA_XSTATS,
							   &p->tcfa_lock, &d,
							   TCA_PAD);
		else
			return 0;
	} else
		err = gnet_stats_start_copy(skb, TCA_ACT_STATS,
					    &p->tcfa_lock, &d, TCA_ACT_PAD);

	if (err < 0)
		goto errout;

	if (gnet_stats_copy_basic(NULL, &d, p->cpu_bstats, &p->tcfa_bstats) < 0 ||
	    gnet_stats_copy_basic_hw(NULL, &d, p->cpu_bstats_hw,
				     &p->tcfa_bstats_hw) < 0 ||
	    gnet_stats_copy_rate_est(&d, &p->tcfa_rate_est) < 0 ||
	    gnet_stats_copy_queue(&d, p->cpu_qstats,
				  &p->tcfa_qstats,
				  p->tcfa_qstats.qlen) < 0)
		goto errout;

	if (gnet_stats_finish_copy(&d) < 0)
		goto errout;

	return 0;

errout:
	return -1;
}