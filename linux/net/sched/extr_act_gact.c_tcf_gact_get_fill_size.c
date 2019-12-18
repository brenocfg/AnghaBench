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
struct tc_gact_p {int dummy; } ;
struct tc_gact {int dummy; } ;
struct tc_action {int dummy; } ;
struct TYPE_2__ {scalar_t__ tcfg_ptype; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 TYPE_1__* to_gact (struct tc_action const*) ; 

__attribute__((used)) static size_t tcf_gact_get_fill_size(const struct tc_action *act)
{
	size_t sz = nla_total_size(sizeof(struct tc_gact)); /* TCA_GACT_PARMS */

#ifdef CONFIG_GACT_PROB
	if (to_gact(act)->tcfg_ptype)
		/* TCA_GACT_PROB */
		sz += nla_total_size(sizeof(struct tc_gact_p));
#endif

	return sz;
}