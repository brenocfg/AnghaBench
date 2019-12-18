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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int xcnt_space; int includes_all_transactions; void* xip; scalar_t__ xcnt; } ;
struct TYPE_5__ {int building_full_snapshot; int /*<<< orphan*/  start_decoding_at; int /*<<< orphan*/  initial_xmin_horizon; TYPE_1__ committed; int /*<<< orphan*/ * reorder; int /*<<< orphan*/  context; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ SnapBuild ;
typedef  int /*<<< orphan*/  ReorderBuffer ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNAPBUILD_START ; 
 void* palloc0 (int) ; 

SnapBuild *
AllocateSnapshotBuilder(ReorderBuffer *reorder,
						TransactionId xmin_horizon,
						XLogRecPtr start_lsn,
						bool need_full_snapshot)
{
	MemoryContext context;
	MemoryContext oldcontext;
	SnapBuild  *builder;

	/* allocate memory in own context, to have better accountability */
	context = AllocSetContextCreate(CurrentMemoryContext,
									"snapshot builder context",
									ALLOCSET_DEFAULT_SIZES);
	oldcontext = MemoryContextSwitchTo(context);

	builder = palloc0(sizeof(SnapBuild));

	builder->state = SNAPBUILD_START;
	builder->context = context;
	builder->reorder = reorder;
	/* Other struct members initialized by zeroing via palloc0 above */

	builder->committed.xcnt = 0;
	builder->committed.xcnt_space = 128;	/* arbitrary number */
	builder->committed.xip =
		palloc0(builder->committed.xcnt_space * sizeof(TransactionId));
	builder->committed.includes_all_transactions = true;

	builder->initial_xmin_horizon = xmin_horizon;
	builder->start_decoding_at = start_lsn;
	builder->building_full_snapshot = need_full_snapshot;

	MemoryContextSwitchTo(oldcontext);

	return builder;
}