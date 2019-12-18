#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tupstate; int /*<<< orphan*/  xid; int /*<<< orphan*/  pointer; int /*<<< orphan*/  nextOffset; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  myXid; int /*<<< orphan*/  deadTupleStorage; } ;
typedef  TYPE_1__ SpGistState ;
typedef  TYPE_2__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SGDTSIZE ; 
 int SPGIST_REDIRECT ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 

SpGistDeadTuple
spgFormDeadTuple(SpGistState *state, int tupstate,
				 BlockNumber blkno, OffsetNumber offnum)
{
	SpGistDeadTuple tuple = (SpGistDeadTuple) state->deadTupleStorage;

	tuple->tupstate = tupstate;
	tuple->size = SGDTSIZE;
	tuple->nextOffset = InvalidOffsetNumber;

	if (tupstate == SPGIST_REDIRECT)
	{
		ItemPointerSet(&tuple->pointer, blkno, offnum);
		Assert(TransactionIdIsValid(state->myXid));
		tuple->xid = state->myXid;
	}
	else
	{
		ItemPointerSetInvalid(&tuple->pointer);
		tuple->xid = InvalidTransactionId;
	}

	return tuple;
}