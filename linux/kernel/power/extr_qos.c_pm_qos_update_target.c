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
struct pm_qos_constraints {int default_value; scalar_t__ notifiers; int /*<<< orphan*/  list; } ;
struct plist_node {int dummy; } ;
typedef  enum pm_qos_req_action { ____Placeholder_pm_qos_req_action } pm_qos_req_action ;

/* Variables and functions */
#define  PM_QOS_ADD_REQ 130 
 int PM_QOS_DEFAULT_VALUE ; 
#define  PM_QOS_REMOVE_REQ 129 
#define  PM_QOS_UPDATE_REQ 128 
 int /*<<< orphan*/  blocking_notifier_call_chain (scalar_t__,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_add (struct plist_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (struct plist_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_node_init (struct plist_node*,int) ; 
 int pm_qos_get_value (struct pm_qos_constraints*) ; 
 int /*<<< orphan*/  pm_qos_lock ; 
 int /*<<< orphan*/  pm_qos_set_value (struct pm_qos_constraints*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_pm_qos_update_target (int,int,int) ; 

int pm_qos_update_target(struct pm_qos_constraints *c, struct plist_node *node,
			 enum pm_qos_req_action action, int value)
{
	unsigned long flags;
	int prev_value, curr_value, new_value;
	int ret;

	spin_lock_irqsave(&pm_qos_lock, flags);
	prev_value = pm_qos_get_value(c);
	if (value == PM_QOS_DEFAULT_VALUE)
		new_value = c->default_value;
	else
		new_value = value;

	switch (action) {
	case PM_QOS_REMOVE_REQ:
		plist_del(node, &c->list);
		break;
	case PM_QOS_UPDATE_REQ:
		/*
		 * to change the list, we atomically remove, reinit
		 * with new value and add, then see if the extremal
		 * changed
		 */
		plist_del(node, &c->list);
		/* fall through */
	case PM_QOS_ADD_REQ:
		plist_node_init(node, new_value);
		plist_add(node, &c->list);
		break;
	default:
		/* no action */
		;
	}

	curr_value = pm_qos_get_value(c);
	pm_qos_set_value(c, curr_value);

	spin_unlock_irqrestore(&pm_qos_lock, flags);

	trace_pm_qos_update_target(action, prev_value, curr_value);
	if (prev_value != curr_value) {
		ret = 1;
		if (c->notifiers)
			blocking_notifier_call_chain(c->notifiers,
						     (unsigned long)curr_value,
						     NULL);
	} else {
		ret = 0;
	}
	return ret;
}