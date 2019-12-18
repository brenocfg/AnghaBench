#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tc_action {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  psample_group; } ;
struct flow_action_entry {TYPE_2__ sample; int /*<<< orphan*/  destructor_priv; int /*<<< orphan*/  destructor; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_psample_group ) (struct tc_action const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tc_action const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_sample_get_group(struct flow_action_entry *entry,
				 const struct tc_action *act)
{
#ifdef CONFIG_NET_CLS_ACT
	entry->sample.psample_group =
		act->ops->get_psample_group(act, &entry->destructor);
	entry->destructor_priv = entry->sample.psample_group;
#endif
}