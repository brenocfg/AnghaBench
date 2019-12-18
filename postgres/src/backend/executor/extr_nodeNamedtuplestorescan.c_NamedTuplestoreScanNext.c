#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_2__ ps; } ;
struct TYPE_9__ {int /*<<< orphan*/  relation; int /*<<< orphan*/  readptr; TYPE_3__ ss; } ;
struct TYPE_6__ {int /*<<< orphan*/  es_direction; } ;
typedef  TYPE_4__ NamedTuplestoreScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
NamedTuplestoreScanNext(NamedTuplestoreScanState *node)
{
	TupleTableSlot *slot;

	/* We intentionally do not support backward scan. */
	Assert(ScanDirectionIsForward(node->ss.ps.state->es_direction));

	/*
	 * Get the next tuple from tuplestore. Return NULL if no more tuples.
	 */
	slot = node->ss.ss_ScanTupleSlot;
	tuplestore_select_read_pointer(node->relation, node->readptr);
	(void) tuplestore_gettupleslot(node->relation, true, false, slot);
	return slot;
}