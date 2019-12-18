#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tts_mcxt; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/  MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecCopySlotMinimalTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tts_minimal_copyslot(TupleTableSlot *dstslot, TupleTableSlot *srcslot)
{
	MemoryContext oldcontext;
	MinimalTuple mintuple;

	oldcontext = MemoryContextSwitchTo(dstslot->tts_mcxt);
	mintuple = ExecCopySlotMinimalTuple(srcslot);
	MemoryContextSwitchTo(oldcontext);

	ExecStoreMinimalTuple(mintuple, dstslot, true);
}