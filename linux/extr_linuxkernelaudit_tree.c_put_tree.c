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
struct audit_tree {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  kfree_rcu (struct audit_tree*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void put_tree(struct audit_tree *tree)
{
	if (refcount_dec_and_test(&tree->count))
		kfree_rcu(tree, head);
}