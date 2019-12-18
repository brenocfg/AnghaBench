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
struct audit_context {int tree_count; struct audit_tree_refs* trees; struct audit_tree_refs* first_trees; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct audit_tree_refs* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grow_tree_refs(struct audit_context *ctx)
{
	struct audit_tree_refs *p = ctx->trees;
	ctx->trees = kzalloc(sizeof(struct audit_tree_refs), GFP_KERNEL);
	if (!ctx->trees) {
		ctx->trees = p;
		return 0;
	}
	if (p)
		p->next = ctx->trees;
	else
		ctx->first_trees = ctx->trees;
	ctx->tree_count = 31;
	return 1;
}