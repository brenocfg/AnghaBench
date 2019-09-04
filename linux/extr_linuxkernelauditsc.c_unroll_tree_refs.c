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
struct audit_tree_refs {int dummy; } ;
struct audit_context {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void unroll_tree_refs(struct audit_context *ctx,
		      struct audit_tree_refs *p, int count)
{
#ifdef CONFIG_AUDIT_TREE
	struct audit_tree_refs *q;
	int n;
	if (!p) {
		/* we started with empty chain */
		p = ctx->first_trees;
		count = 31;
		/* if the very first allocation has failed, nothing to do */
		if (!p)
			return;
	}
	n = count;
	for (q = p; q != ctx->trees; q = q->next, n = 31) {
		while (n--) {
			audit_put_chunk(q->c[n]);
			q->c[n] = NULL;
		}
	}
	while (n-- > ctx->tree_count) {
		audit_put_chunk(q->c[n]);
		q->c[n] = NULL;
	}
	ctx->trees = p;
	ctx->tree_count = count;
#endif
}