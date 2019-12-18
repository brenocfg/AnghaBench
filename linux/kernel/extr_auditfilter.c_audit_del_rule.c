#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct audit_tree {int dummy; } ;
struct TYPE_4__ {int listnr; int /*<<< orphan*/  list; scalar_t__ exe; struct audit_tree* tree; scalar_t__ watch; } ;
struct audit_entry {int /*<<< orphan*/  rcu; TYPE_1__ rule; int /*<<< orphan*/  list; } ;

/* Variables and functions */
#define  AUDIT_FILTER_EXCLUDE 130 
#define  AUDIT_FILTER_FS 129 
#define  AUDIT_FILTER_USER 128 
 int ENOENT ; 
 int /*<<< orphan*/  audit_filter_mutex ; 
 struct audit_entry* audit_find_rule (struct audit_entry*,struct list_head**) ; 
 int /*<<< orphan*/  audit_free_rule_rcu ; 
 int /*<<< orphan*/  audit_match_signal (struct audit_entry*) ; 
 int /*<<< orphan*/  audit_n_rules ; 
 int /*<<< orphan*/  audit_put_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  audit_remove_mark_rule (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_remove_tree_rule (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_remove_watch_rule (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_signals ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int audit_del_rule(struct audit_entry *entry)
{
	struct audit_entry  *e;
	struct audit_tree *tree = entry->rule.tree;
	struct list_head *list;
	int ret = 0;
#ifdef CONFIG_AUDITSYSCALL
	int dont_count = 0;

	/* If any of these, don't count towards total */
	switch(entry->rule.listnr) {
	case AUDIT_FILTER_USER:
	case AUDIT_FILTER_EXCLUDE:
	case AUDIT_FILTER_FS:
		dont_count = 1;
	}
#endif

	mutex_lock(&audit_filter_mutex);
	e = audit_find_rule(entry, &list);
	if (!e) {
		ret = -ENOENT;
		goto out;
	}

	if (e->rule.watch)
		audit_remove_watch_rule(&e->rule);

	if (e->rule.tree)
		audit_remove_tree_rule(&e->rule);

	if (e->rule.exe)
		audit_remove_mark_rule(&e->rule);

#ifdef CONFIG_AUDITSYSCALL
	if (!dont_count)
		audit_n_rules--;

	if (!audit_match_signal(entry))
		audit_signals--;
#endif

	list_del_rcu(&e->list);
	list_del(&e->rule.list);
	call_rcu(&e->rcu, audit_free_rule_rcu);

out:
	mutex_unlock(&audit_filter_mutex);

	if (tree)
		audit_put_tree(tree);	/* that's the temporary one */

	return ret;
}