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
struct policydb {int dummy; } ;
struct cond_node {int cur_state; struct cond_av_list* false_list; struct cond_av_list* true_list; int /*<<< orphan*/  expr; } ;
struct cond_av_list {TYPE_2__* node; struct cond_av_list* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  specified; } ;
struct TYPE_4__ {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVTAB_ENABLED ; 
 int cond_evaluate_expr (struct policydb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int evaluate_cond_node(struct policydb *p, struct cond_node *node)
{
	int new_state;
	struct cond_av_list *cur;

	new_state = cond_evaluate_expr(p, node->expr);
	if (new_state != node->cur_state) {
		node->cur_state = new_state;
		if (new_state == -1)
			pr_err("SELinux: expression result was undefined - disabling all rules.\n");
		/* turn the rules on or off */
		for (cur = node->true_list; cur; cur = cur->next) {
			if (new_state <= 0)
				cur->node->key.specified &= ~AVTAB_ENABLED;
			else
				cur->node->key.specified |= AVTAB_ENABLED;
		}

		for (cur = node->false_list; cur; cur = cur->next) {
			/* -1 or 1 */
			if (new_state)
				cur->node->key.specified &= ~AVTAB_ENABLED;
			else
				cur->node->key.specified |= AVTAB_ENABLED;
		}
	}
	return 0;
}