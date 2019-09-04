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
struct hist_trigger_attrs {unsigned int n_assignments; unsigned int n_actions; struct hist_trigger_attrs* clock; struct hist_trigger_attrs* vals_str; struct hist_trigger_attrs* keys_str; struct hist_trigger_attrs* sort_key_str; struct hist_trigger_attrs* name; struct hist_trigger_attrs** action_str; struct hist_trigger_attrs** assignment_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hist_trigger_attrs*) ; 

__attribute__((used)) static void destroy_hist_trigger_attrs(struct hist_trigger_attrs *attrs)
{
	unsigned int i;

	if (!attrs)
		return;

	for (i = 0; i < attrs->n_assignments; i++)
		kfree(attrs->assignment_str[i]);

	for (i = 0; i < attrs->n_actions; i++)
		kfree(attrs->action_str[i]);

	kfree(attrs->name);
	kfree(attrs->sort_key_str);
	kfree(attrs->keys_str);
	kfree(attrs->vals_str);
	kfree(attrs->clock);
	kfree(attrs);
}