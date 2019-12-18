#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tuplehash_hash {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  TYPE_1__* TupleHashTable ;
struct TYPE_5__ {int /*<<< orphan*/ * ecxt_outertuple; int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_eq_func; int /*<<< orphan*/ * inputslot; int /*<<< orphan*/ * tableslot; TYPE_2__* exprcontext; } ;
typedef  int /*<<< orphan*/ * MinimalTuple ;
typedef  TYPE_2__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
TupleHashTableMatch(struct tuplehash_hash *tb, const MinimalTuple tuple1, const MinimalTuple tuple2)
{
	TupleTableSlot *slot1;
	TupleTableSlot *slot2;
	TupleHashTable hashtable = (TupleHashTable) tb->private_data;
	ExprContext *econtext = hashtable->exprcontext;

	/*
	 * We assume that simplehash.h will only ever call us with the first
	 * argument being an actual table entry, and the second argument being
	 * LookupTupleHashEntry's dummy TupleHashEntryData.  The other direction
	 * could be supported too, but is not currently required.
	 */
	Assert(tuple1 != NULL);
	slot1 = hashtable->tableslot;
	ExecStoreMinimalTuple(tuple1, slot1, false);
	Assert(tuple2 == NULL);
	slot2 = hashtable->inputslot;

	/* For crosstype comparisons, the inputslot must be first */
	econtext->ecxt_innertuple = slot2;
	econtext->ecxt_outertuple = slot1;
	return !ExecQualAndReset(hashtable->cur_eq_func, econtext);
}