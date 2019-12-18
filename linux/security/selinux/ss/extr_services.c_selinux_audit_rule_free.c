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
struct selinux_audit_rule {int /*<<< orphan*/  au_ctxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct selinux_audit_rule*) ; 

void selinux_audit_rule_free(void *vrule)
{
	struct selinux_audit_rule *rule = vrule;

	if (rule) {
		context_destroy(&rule->au_ctxt);
		kfree(rule);
	}
}