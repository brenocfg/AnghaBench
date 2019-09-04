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
struct audit_tree_refs {struct audit_tree_refs* next; } ;
struct audit_context {struct audit_tree_refs* first_trees; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct audit_tree_refs*) ; 

__attribute__((used)) static void free_tree_refs(struct audit_context *ctx)
{
	struct audit_tree_refs *p, *q;
	for (p = ctx->first_trees; p; p = q) {
		q = p->next;
		kfree(p);
	}
}