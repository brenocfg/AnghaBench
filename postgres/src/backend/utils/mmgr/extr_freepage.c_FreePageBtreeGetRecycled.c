#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  btree_recycle_count; int /*<<< orphan*/  btree_recycle; } ;
struct TYPE_8__ {int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ FreePageSpanLeader ;
typedef  TYPE_2__ FreePageManager ;
typedef  int /*<<< orphan*/  FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_pointer_is_page_aligned (char*,TYPE_1__*) ; 
 char* fpm_segment_base (TYPE_2__*) ; 
 TYPE_1__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_store (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static FreePageBtree *
FreePageBtreeGetRecycled(FreePageManager *fpm)
{
	char	   *base = fpm_segment_base(fpm);
	FreePageSpanLeader *victim = relptr_access(base, fpm->btree_recycle);
	FreePageSpanLeader *newhead;

	Assert(victim != NULL);
	newhead = relptr_access(base, victim->next);
	if (newhead != NULL)
		relptr_copy(newhead->prev, victim->prev);
	relptr_store(base, fpm->btree_recycle, newhead);
	Assert(fpm_pointer_is_page_aligned(base, victim));
	fpm->btree_recycle_count--;
	return (FreePageBtree *) victim;
}