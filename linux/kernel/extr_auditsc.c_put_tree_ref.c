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
struct audit_tree_refs {struct audit_chunk** c; struct audit_tree_refs* next; } ;
struct audit_context {int tree_count; struct audit_tree_refs* trees; } ;
struct audit_chunk {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static int put_tree_ref(struct audit_context *ctx, struct audit_chunk *chunk)
{
	struct audit_tree_refs *p = ctx->trees;
	int left = ctx->tree_count;
	if (likely(left)) {
		p->c[--left] = chunk;
		ctx->tree_count = left;
		return 1;
	}
	if (!p)
		return 0;
	p = p->next;
	if (p) {
		p->c[30] = chunk;
		ctx->trees = p;
		ctx->tree_count = 30;
		return 1;
	}
	return 0;
}