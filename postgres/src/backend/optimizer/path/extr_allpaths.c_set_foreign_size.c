#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  relid; } ;
struct TYPE_9__ {int /*<<< orphan*/  rows; TYPE_1__* fdwroutine; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* GetForeignRelSize ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  clamp_row_est (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_foreign_size_estimates (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_foreign_size(PlannerInfo *root, RelOptInfo *rel, RangeTblEntry *rte)
{
	/* Mark rel with estimated output rows, width, etc */
	set_foreign_size_estimates(root, rel);

	/* Let FDW adjust the size estimates, if it can */
	rel->fdwroutine->GetForeignRelSize(root, rel, rte->relid);

	/* ... but do not let it set the rows estimate to zero */
	rel->rows = clamp_row_est(rel->rows);
}