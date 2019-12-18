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
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_build; int /*<<< orphan*/  heapRel; int /*<<< orphan*/  freespace; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_1__ GISTInsertState ;
typedef  TYPE_2__ GISTInsertStack ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIST_UNLOCK ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistfinishsplit (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int gistplacetopage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
gistinserttuples(GISTInsertState *state, GISTInsertStack *stack,
				 GISTSTATE *giststate,
				 IndexTuple *tuples, int ntup, OffsetNumber oldoffnum,
				 Buffer leftchild, Buffer rightchild,
				 bool unlockbuf, bool unlockleftchild)
{
	List	   *splitinfo;
	bool		is_split;

	/*
	 * Check for any rw conflicts (in serializable isolation level) just
	 * before we intend to modify the page
	 */
	CheckForSerializableConflictIn(state->r, NULL, stack->buffer);

	/* Insert the tuple(s) to the page, splitting the page if necessary */
	is_split = gistplacetopage(state->r, state->freespace, giststate,
							   stack->buffer,
							   tuples, ntup,
							   oldoffnum, NULL,
							   leftchild,
							   &splitinfo,
							   true,
							   state->heapRel,
							   state->is_build);

	/*
	 * Before recursing up in case the page was split, release locks on the
	 * child pages. We don't need to keep them locked when updating the
	 * parent.
	 */
	if (BufferIsValid(rightchild))
		UnlockReleaseBuffer(rightchild);
	if (BufferIsValid(leftchild) && unlockleftchild)
		LockBuffer(leftchild, GIST_UNLOCK);

	/*
	 * If we had to split, insert/update the downlinks in the parent. If the
	 * caller requested us to release the lock on stack->buffer, tell
	 * gistfinishsplit() to do that as soon as it's safe to do so. If we
	 * didn't have to split, release it ourselves.
	 */
	if (splitinfo)
		gistfinishsplit(state, stack, giststate, splitinfo, unlockbuf);
	else if (unlockbuf)
		LockBuffer(stack->buffer, GIST_UNLOCK);

	return is_split;
}