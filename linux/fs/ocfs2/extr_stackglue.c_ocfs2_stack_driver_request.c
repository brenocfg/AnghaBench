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
struct ocfs2_stack_plugin {char const* sp_name; int /*<<< orphan*/  sp_count; int /*<<< orphan*/  sp_owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 struct ocfs2_stack_plugin* active_stack ; 
 char const* cluster_stack_name ; 
 int /*<<< orphan*/  ocfs2_stack_lock ; 
 struct ocfs2_stack_plugin* ocfs2_stack_lookup (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_stack_driver_request(const char *stack_name,
				      const char *plugin_name)
{
	int rc;
	struct ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);

	/*
	 * If the stack passed by the filesystem isn't the selected one,
	 * we can't continue.
	 */
	if (strcmp(stack_name, cluster_stack_name)) {
		rc = -EBUSY;
		goto out;
	}

	if (active_stack) {
		/*
		 * If the active stack isn't the one we want, it cannot
		 * be selected right now.
		 */
		if (!strcmp(active_stack->sp_name, plugin_name))
			rc = 0;
		else
			rc = -EBUSY;
		goto out;
	}

	p = ocfs2_stack_lookup(plugin_name);
	if (!p || !try_module_get(p->sp_owner)) {
		rc = -ENOENT;
		goto out;
	}

	active_stack = p;
	rc = 0;

out:
	/* If we found it, pin it */
	if (!rc)
		active_stack->sp_count++;

	spin_unlock(&ocfs2_stack_lock);
	return rc;
}