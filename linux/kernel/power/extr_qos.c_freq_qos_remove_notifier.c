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
struct notifier_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifiers; } ;
struct TYPE_3__ {int /*<<< orphan*/  notifiers; } ;
struct freq_constraints {TYPE_2__ max_freq; TYPE_1__ min_freq; } ;
typedef  enum freq_qos_req_type { ____Placeholder_freq_qos_req_type } freq_qos_req_type ;

/* Variables and functions */
 int EINVAL ; 
#define  FREQ_QOS_MAX 129 
#define  FREQ_QOS_MIN 128 
 scalar_t__ IS_ERR_OR_NULL (struct freq_constraints*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ ,struct notifier_block*) ; 

int freq_qos_remove_notifier(struct freq_constraints *qos,
			     enum freq_qos_req_type type,
			     struct notifier_block *notifier)
{
	int ret;

	if (IS_ERR_OR_NULL(qos) || !notifier)
		return -EINVAL;

	switch (type) {
	case FREQ_QOS_MIN:
		ret = blocking_notifier_chain_unregister(qos->min_freq.notifiers,
							 notifier);
		break;
	case FREQ_QOS_MAX:
		ret = blocking_notifier_chain_unregister(qos->max_freq.notifiers,
							 notifier);
		break;
	default:
		WARN_ON(1);
		ret = -EINVAL;
	}

	return ret;
}