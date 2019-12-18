#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ maxoff; } ;
struct TYPE_9__ {int /*<<< orphan*/  sizeOfBloomTuple; } ;
struct TYPE_8__ {scalar_t__ pd_lower; scalar_t__ pd_upper; } ;
typedef  scalar_t__ Pointer ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  BloomTuple ;
typedef  TYPE_2__ BloomState ;
typedef  TYPE_3__* BloomPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BloomPageGetFreeSpace (TYPE_2__*,scalar_t__) ; 
 TYPE_3__* BloomPageGetOpaque (scalar_t__) ; 
 int /*<<< orphan*/ * BloomPageGetTuple (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BloomPageIsDeleted (scalar_t__) ; 
 int /*<<< orphan*/  PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

bool
BloomPageAddItem(BloomState *state, Page page, BloomTuple *tuple)
{
	BloomTuple *itup;
	BloomPageOpaque opaque;
	Pointer		ptr;

	/* We shouldn't be pointed to an invalid page */
	Assert(!PageIsNew(page) && !BloomPageIsDeleted(page));

	/* Does new tuple fit on the page? */
	if (BloomPageGetFreeSpace(state, page) < state->sizeOfBloomTuple)
		return false;

	/* Copy new tuple to the end of page */
	opaque = BloomPageGetOpaque(page);
	itup = BloomPageGetTuple(state, page, opaque->maxoff + 1);
	memcpy((Pointer) itup, (Pointer) tuple, state->sizeOfBloomTuple);

	/* Adjust maxoff and pd_lower */
	opaque->maxoff++;
	ptr = (Pointer) BloomPageGetTuple(state, page, opaque->maxoff + 1);
	((PageHeader) page)->pd_lower = ptr - page;

	/* Assert we didn't overrun available space */
	Assert(((PageHeader) page)->pd_lower <= ((PageHeader) page)->pd_upper);

	return true;
}