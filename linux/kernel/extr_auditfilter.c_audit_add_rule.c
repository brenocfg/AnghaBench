#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct audit_watch {int dummy; } ;
struct audit_tree {int dummy; } ;
struct TYPE_3__ {int listnr; unsigned long long prio; int flags; int /*<<< orphan*/  list; struct audit_tree* tree; struct audit_watch* watch; } ;
struct audit_entry {int /*<<< orphan*/  list; TYPE_1__ rule; } ;

/* Variables and functions */
#define  AUDIT_FILTER_EXCLUDE 130 
 int AUDIT_FILTER_EXIT ; 
#define  AUDIT_FILTER_FS 129 
 int AUDIT_FILTER_PREPEND ; 
#define  AUDIT_FILTER_USER 128 
 int EEXIST ; 
 int audit_add_tree_rule (TYPE_1__*) ; 
 int audit_add_watch (TYPE_1__*,struct list_head**) ; 
 int /*<<< orphan*/  audit_filter_mutex ; 
 struct audit_entry* audit_find_rule (struct audit_entry*,struct list_head**) ; 
 int /*<<< orphan*/  audit_match_signal (struct audit_entry*) ; 
 int /*<<< orphan*/  audit_n_rules ; 
 int /*<<< orphan*/  audit_put_tree (struct audit_tree*) ; 
 int /*<<< orphan*/ * audit_rules_list ; 
 int /*<<< orphan*/  audit_signals ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long long prio_high ; 
 unsigned long long prio_low ; 

__attribute__((used)) static inline int audit_add_rule(struct audit_entry *entry)
{
	struct audit_entry *e;
	struct audit_watch *watch = entry->rule.watch;
	struct audit_tree *tree = entry->rule.tree;
	struct list_head *list;
	int err = 0;
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
	if (e) {
		mutex_unlock(&audit_filter_mutex);
		err = -EEXIST;
		/* normally audit_add_tree_rule() will free it on failure */
		if (tree)
			audit_put_tree(tree);
		return err;
	}

	if (watch) {
		/* audit_filter_mutex is dropped and re-taken during this call */
		err = audit_add_watch(&entry->rule, &list);
		if (err) {
			mutex_unlock(&audit_filter_mutex);
			/*
			 * normally audit_add_tree_rule() will free it
			 * on failure
			 */
			if (tree)
				audit_put_tree(tree);
			return err;
		}
	}
	if (tree) {
		err = audit_add_tree_rule(&entry->rule);
		if (err) {
			mutex_unlock(&audit_filter_mutex);
			return err;
		}
	}

	entry->rule.prio = ~0ULL;
	if (entry->rule.listnr == AUDIT_FILTER_EXIT) {
		if (entry->rule.flags & AUDIT_FILTER_PREPEND)
			entry->rule.prio = ++prio_high;
		else
			entry->rule.prio = --prio_low;
	}

	if (entry->rule.flags & AUDIT_FILTER_PREPEND) {
		list_add(&entry->rule.list,
			 &audit_rules_list[entry->rule.listnr]);
		list_add_rcu(&entry->list, list);
		entry->rule.flags &= ~AUDIT_FILTER_PREPEND;
	} else {
		list_add_tail(&entry->rule.list,
			      &audit_rules_list[entry->rule.listnr]);
		list_add_tail_rcu(&entry->list, list);
	}
#ifdef CONFIG_AUDITSYSCALL
	if (!dont_count)
		audit_n_rules++;

	if (!audit_match_signal(entry))
		audit_signals++;
#endif
	mutex_unlock(&audit_filter_mutex);

	return err;
}