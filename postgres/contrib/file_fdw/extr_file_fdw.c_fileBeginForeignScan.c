#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* filename; int is_program; int /*<<< orphan*/  cstate; int /*<<< orphan*/ * options; } ;
struct TYPE_10__ {int /*<<< orphan*/  fdw_private; } ;
struct TYPE_7__ {scalar_t__ plan; } ;
struct TYPE_8__ {int /*<<< orphan*/  ss_currentRelation; TYPE_1__ ps; } ;
struct TYPE_9__ {void* fdw_state; TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ ForeignScan ;
typedef  TYPE_5__ FileFdwExecutionState ;
typedef  int /*<<< orphan*/  CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  BeginCopyFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EXEC_FLAG_EXPLAIN_ONLY ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileGetOptions (int /*<<< orphan*/ ,char**,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
fileBeginForeignScan(ForeignScanState *node, int eflags)
{
	ForeignScan *plan = (ForeignScan *) node->ss.ps.plan;
	char	   *filename;
	bool		is_program;
	List	   *options;
	CopyState	cstate;
	FileFdwExecutionState *festate;

	/*
	 * Do nothing in EXPLAIN (no ANALYZE) case.  node->fdw_state stays NULL.
	 */
	if (eflags & EXEC_FLAG_EXPLAIN_ONLY)
		return;

	/* Fetch options of foreign table */
	fileGetOptions(RelationGetRelid(node->ss.ss_currentRelation),
				   &filename, &is_program, &options);

	/* Add any options from the plan (currently only convert_selectively) */
	options = list_concat(options, plan->fdw_private);

	/*
	 * Create CopyState from FDW options.  We always acquire all columns, so
	 * as to match the expected ScanTupleSlot signature.
	 */
	cstate = BeginCopyFrom(NULL,
						   node->ss.ss_currentRelation,
						   filename,
						   is_program,
						   NULL,
						   NIL,
						   options);

	/*
	 * Save state in node->fdw_state.  We must save enough information to call
	 * BeginCopyFrom() again.
	 */
	festate = (FileFdwExecutionState *) palloc(sizeof(FileFdwExecutionState));
	festate->filename = filename;
	festate->is_program = is_program;
	festate->options = options;
	festate->cstate = cstate;

	node->fdw_state = (void *) festate;
}