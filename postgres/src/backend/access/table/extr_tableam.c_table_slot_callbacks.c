#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlotOps ;
struct TYPE_8__ {TYPE_2__* rd_rel; TYPE_1__* rd_tableam; } ;
struct TYPE_7__ {scalar_t__ relkind; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* slot_callbacks ) (TYPE_3__*) ;} ;
typedef  TYPE_3__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  TTSOpsHeapTuple ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*) ; 

const TupleTableSlotOps *
table_slot_callbacks(Relation relation)
{
	const TupleTableSlotOps *tts_cb;

	if (relation->rd_tableam)
		tts_cb = relation->rd_tableam->slot_callbacks(relation);
	else if (relation->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
	{
		/*
		 * Historically FDWs expect to store heap tuples in slots. Continue
		 * handing them one, to make it less painful to adapt FDWs to new
		 * versions. The cost of a heap slot over a virtual slot is pretty
		 * small.
		 */
		tts_cb = &TTSOpsHeapTuple;
	}
	else
	{
		/*
		 * These need to be supported, as some parts of the code (like COPY)
		 * need to create slots for such relations too. It seems better to
		 * centralize the knowledge that a heap slot is the right thing in
		 * that case here.
		 */
		Assert(relation->rd_rel->relkind == RELKIND_VIEW ||
			   relation->rd_rel->relkind == RELKIND_PARTITIONED_TABLE);
		tts_cb = &TTSOpsVirtual;
	}

	return tts_cb;
}