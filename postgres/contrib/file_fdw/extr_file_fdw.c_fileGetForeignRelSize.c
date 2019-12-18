#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  options; int /*<<< orphan*/  is_program; int /*<<< orphan*/  filename; } ;
struct TYPE_6__ {void* fdw_private; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FileFdwPlanState ;

/* Variables and functions */
 int /*<<< orphan*/  estimate_size (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fileGetOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
fileGetForeignRelSize(PlannerInfo *root,
					  RelOptInfo *baserel,
					  Oid foreigntableid)
{
	FileFdwPlanState *fdw_private;

	/*
	 * Fetch options.  We only need filename (or program) at this point, but
	 * we might as well get everything and not need to re-fetch it later in
	 * planning.
	 */
	fdw_private = (FileFdwPlanState *) palloc(sizeof(FileFdwPlanState));
	fileGetOptions(foreigntableid,
				   &fdw_private->filename,
				   &fdw_private->is_program,
				   &fdw_private->options);
	baserel->fdw_private = (void *) fdw_private;

	/* Estimate relation size */
	estimate_size(root, baserel, fdw_private);
}