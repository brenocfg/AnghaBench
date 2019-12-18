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
struct audit_tree {int goner; int /*<<< orphan*/  list; int /*<<< orphan*/  same_root; int /*<<< orphan*/ * root; int /*<<< orphan*/  rules; } ;
struct audit_krule {struct audit_tree* tree; int /*<<< orphan*/  rlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_schedule_prune () ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prune_list ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int audit_remove_tree_rule(struct audit_krule *rule)
{
	struct audit_tree *tree;
	tree = rule->tree;
	if (tree) {
		spin_lock(&hash_lock);
		list_del_init(&rule->rlist);
		if (list_empty(&tree->rules) && !tree->goner) {
			tree->root = NULL;
			list_del_init(&tree->same_root);
			tree->goner = 1;
			list_move(&tree->list, &prune_list);
			rule->tree = NULL;
			spin_unlock(&hash_lock);
			audit_schedule_prune();
			return 1;
		}
		rule->tree = NULL;
		spin_unlock(&hash_lock);
		return 1;
	}
	return 0;
}