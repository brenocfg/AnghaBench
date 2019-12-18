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
struct audit_tree {int /*<<< orphan*/  pathname; int /*<<< orphan*/ * root; int /*<<< orphan*/  same_root; int /*<<< orphan*/  list; int /*<<< orphan*/  rules; int /*<<< orphan*/  chunks; scalar_t__ goner; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct audit_tree* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct audit_tree *alloc_tree(const char *s)
{
	struct audit_tree *tree;

	tree = kmalloc(sizeof(struct audit_tree) + strlen(s) + 1, GFP_KERNEL);
	if (tree) {
		refcount_set(&tree->count, 1);
		tree->goner = 0;
		INIT_LIST_HEAD(&tree->chunks);
		INIT_LIST_HEAD(&tree->rules);
		INIT_LIST_HEAD(&tree->list);
		INIT_LIST_HEAD(&tree->same_root);
		tree->root = NULL;
		strcpy(tree->pathname, s);
	}
	return tree;
}