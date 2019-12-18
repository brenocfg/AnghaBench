#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * freelist; } ;
struct TYPE_7__ {size_t npages; int /*<<< orphan*/  prev; int /*<<< orphan*/  next; int /*<<< orphan*/  magic; } ;
typedef  size_t Size ;
typedef  TYPE_1__ FreePageSpanLeader ;
typedef  TYPE_2__ FreePageManager ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_NUM_FREELISTS ; 
 int /*<<< orphan*/  FREE_PAGE_SPAN_LEADER_MAGIC ; 
 size_t Min (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_page_to_pointer (char*,size_t) ; 
 char* fpm_segment_base (TYPE_2__*) ; 
 TYPE_1__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_store (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
FreePagePushSpanLeader(FreePageManager *fpm, Size first_page, Size npages)
{
	char	   *base = fpm_segment_base(fpm);
	Size		f = Min(npages, FPM_NUM_FREELISTS) - 1;
	FreePageSpanLeader *head = relptr_access(base, fpm->freelist[f]);
	FreePageSpanLeader *span;

	span = (FreePageSpanLeader *) fpm_page_to_pointer(base, first_page);
	span->magic = FREE_PAGE_SPAN_LEADER_MAGIC;
	span->npages = npages;
	relptr_store(base, span->next, head);
	relptr_store(base, span->prev, (FreePageSpanLeader *) NULL);
	if (head != NULL)
		relptr_store(base, head->prev, span);
	relptr_store(base, fpm->freelist[f], span);
}