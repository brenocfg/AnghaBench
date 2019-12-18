#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lateral_relids; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int /*<<< orphan*/  add_partial_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 double compute_bitmap_pages (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int compute_parallel_worker (TYPE_1__*,double,int,int /*<<< orphan*/ ) ; 
 scalar_t__ create_bitmap_heap_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  max_parallel_workers_per_gather ; 

void
create_partial_bitmap_paths(PlannerInfo *root, RelOptInfo *rel,
							Path *bitmapqual)
{
	int			parallel_workers;
	double		pages_fetched;

	/* Compute heap pages for bitmap heap scan */
	pages_fetched = compute_bitmap_pages(root, rel, bitmapqual, 1.0,
										 NULL, NULL);

	parallel_workers = compute_parallel_worker(rel, pages_fetched, -1,
											   max_parallel_workers_per_gather);

	if (parallel_workers <= 0)
		return;

	add_partial_path(rel, (Path *) create_bitmap_heap_path(root, rel,
														   bitmapqual, rel->lateral_relids, 1.0, parallel_workers));
}