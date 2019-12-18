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
struct aa_audit_rule {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aa_audit_rule*) ; 

void aa_audit_rule_free(void *vrule)
{
	struct aa_audit_rule *rule = vrule;

	if (rule) {
		if (!IS_ERR(rule->label))
			aa_put_label(rule->label);
		kfree(rule);
	}
}