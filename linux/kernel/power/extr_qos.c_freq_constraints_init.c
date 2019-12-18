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
struct pm_qos_constraints {int /*<<< orphan*/ * notifiers; int /*<<< orphan*/  type; void* no_constraint_value; void* default_value; void* target_value; int /*<<< orphan*/  list; } ;
struct freq_constraints {int /*<<< orphan*/  max_freq_notifiers; struct pm_qos_constraints max_freq; int /*<<< orphan*/  min_freq_notifiers; struct pm_qos_constraints min_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 void* FREQ_QOS_MAX_DEFAULT_VALUE ; 
 void* FREQ_QOS_MIN_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PM_QOS_MAX ; 
 int /*<<< orphan*/  PM_QOS_MIN ; 
 int /*<<< orphan*/  plist_head_init (int /*<<< orphan*/ *) ; 

void freq_constraints_init(struct freq_constraints *qos)
{
	struct pm_qos_constraints *c;

	c = &qos->min_freq;
	plist_head_init(&c->list);
	c->target_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->default_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->no_constraint_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->type = PM_QOS_MAX;
	c->notifiers = &qos->min_freq_notifiers;
	BLOCKING_INIT_NOTIFIER_HEAD(c->notifiers);

	c = &qos->max_freq;
	plist_head_init(&c->list);
	c->target_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->default_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->no_constraint_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->type = PM_QOS_MIN;
	c->notifiers = &qos->max_freq_notifiers;
	BLOCKING_INIT_NOTIFIER_HEAD(c->notifiers);
}