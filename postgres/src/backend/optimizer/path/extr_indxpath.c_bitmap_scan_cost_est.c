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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  param_info; scalar_t__ parallel_workers; int /*<<< orphan*/  pathkeys; int /*<<< orphan*/  pathtarget; TYPE_1__* parent; int /*<<< orphan*/  pathtype; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_4__ path; int /*<<< orphan*/ * bitmapqual; } ;
struct TYPE_7__ {int /*<<< orphan*/  relid; int /*<<< orphan*/  reltarget; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  Cost ;
typedef  TYPE_2__ BitmapHeapPath ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  T_BitmapHeapPath ; 
 int /*<<< orphan*/  T_BitmapHeapScan ; 
 int /*<<< orphan*/  cost_bitmap_heap_scan (TYPE_4__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_baserel_parampathinfo (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bitmap_tree_required_outer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_loop_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Cost
bitmap_scan_cost_est(PlannerInfo *root, RelOptInfo *rel, Path *ipath)
{
	BitmapHeapPath bpath;
	Relids		required_outer;

	/* Identify required outer rels, in case it's a parameterized scan */
	required_outer = get_bitmap_tree_required_outer(ipath);

	/* Set up a dummy BitmapHeapPath */
	bpath.path.type = T_BitmapHeapPath;
	bpath.path.pathtype = T_BitmapHeapScan;
	bpath.path.parent = rel;
	bpath.path.pathtarget = rel->reltarget;
	bpath.path.param_info = get_baserel_parampathinfo(root, rel,
													  required_outer);
	bpath.path.pathkeys = NIL;
	bpath.bitmapqual = ipath;

	/*
	 * Check the cost of temporary path without considering parallelism.
	 * Parallel bitmap heap path will be considered at later stage.
	 */
	bpath.path.parallel_workers = 0;
	cost_bitmap_heap_scan(&bpath.path, root, rel,
						  bpath.path.param_info,
						  ipath,
						  get_loop_count(root, rel->relid, required_outer));

	return bpath.path.total_cost;
}