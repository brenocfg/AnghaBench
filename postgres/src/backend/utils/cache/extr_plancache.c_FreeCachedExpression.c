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
struct TYPE_3__ {scalar_t__ magic; int /*<<< orphan*/  context; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ CachedExpression ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDEXPR_MAGIC ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 

void
FreeCachedExpression(CachedExpression *cexpr)
{
	/* Sanity check */
	Assert(cexpr->magic == CACHEDEXPR_MAGIC);
	/* Unlink from global list */
	dlist_delete(&cexpr->node);
	/* Free all storage associated with CachedExpression */
	MemoryContextDelete(cexpr->context);
}