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
struct tc_action {TYPE_1__* ops; } ;
struct flow_action_entry {scalar_t__ dev; scalar_t__ destructor_priv; int /*<<< orphan*/  destructor; } ;
struct TYPE_2__ {scalar_t__ (* get_dev ) (struct tc_action const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct tc_action const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_mirred_get_dev(struct flow_action_entry *entry,
			       const struct tc_action *act)
{
#ifdef CONFIG_NET_CLS_ACT
	entry->dev = act->ops->get_dev(act, &entry->destructor);
	if (!entry->dev)
		return;
	entry->destructor_priv = entry->dev;
#endif
}