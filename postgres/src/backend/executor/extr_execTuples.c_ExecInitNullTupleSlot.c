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
typedef  int /*<<< orphan*/  TupleTableSlotOps ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecInitExtraTupleSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ExecStoreAllNullTuple (int /*<<< orphan*/ *) ; 

TupleTableSlot *
ExecInitNullTupleSlot(EState *estate, TupleDesc tupType,
					  const TupleTableSlotOps *tts_ops)
{
	TupleTableSlot *slot = ExecInitExtraTupleSlot(estate, tupType, tts_ops);

	return ExecStoreAllNullTuple(slot);
}