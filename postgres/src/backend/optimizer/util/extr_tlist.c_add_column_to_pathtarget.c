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
struct TYPE_3__ {void** sortgrouprefs; int /*<<< orphan*/  exprs; } ;
typedef  TYPE_1__ PathTarget ;
typedef  void* Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 scalar_t__ repalloc (void**,int) ; 

void
add_column_to_pathtarget(PathTarget *target, Expr *expr, Index sortgroupref)
{
	/* Updating the exprs list is easy ... */
	target->exprs = lappend(target->exprs, expr);
	/* ... the sortgroupref data, a bit less so */
	if (target->sortgrouprefs)
	{
		int			nexprs = list_length(target->exprs);

		/* This might look inefficient, but actually it's usually cheap */
		target->sortgrouprefs = (Index *)
			repalloc(target->sortgrouprefs, nexprs * sizeof(Index));
		target->sortgrouprefs[nexprs - 1] = sortgroupref;
	}
	else if (sortgroupref)
	{
		/* Adding sortgroupref labeling to a previously unlabeled target */
		int			nexprs = list_length(target->exprs);

		target->sortgrouprefs = (Index *) palloc0(nexprs * sizeof(Index));
		target->sortgrouprefs[nexprs - 1] = sortgroupref;
	}
}