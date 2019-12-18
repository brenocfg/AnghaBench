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
typedef  size_t u32 ;
struct tcf_t {int dummy; } ;
struct tc_cookie {int len; } ;
struct tc_action {int /*<<< orphan*/  act_cookie; } ;
struct gnet_stats_queue {int dummy; } ;
struct gnet_stats_basic {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 
 struct tc_cookie* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static size_t tcf_action_shared_attrs_size(const struct tc_action *act)
{
	struct tc_cookie *act_cookie;
	u32 cookie_len = 0;

	rcu_read_lock();
	act_cookie = rcu_dereference(act->act_cookie);

	if (act_cookie)
		cookie_len = nla_total_size(act_cookie->len);
	rcu_read_unlock();

	return  nla_total_size(0) /* action number nested */
		+ nla_total_size(IFNAMSIZ) /* TCA_ACT_KIND */
		+ cookie_len /* TCA_ACT_COOKIE */
		+ nla_total_size(0) /* TCA_ACT_STATS nested */
		/* TCA_STATS_BASIC */
		+ nla_total_size_64bit(sizeof(struct gnet_stats_basic))
		/* TCA_STATS_QUEUE */
		+ nla_total_size_64bit(sizeof(struct gnet_stats_queue))
		+ nla_total_size(0) /* TCA_OPTIONS nested */
		+ nla_total_size(sizeof(struct tcf_t)); /* TCA_GACT_TM */
}