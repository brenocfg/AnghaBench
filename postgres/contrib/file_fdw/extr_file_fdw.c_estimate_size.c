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
struct stat {int st_size; } ;
struct TYPE_8__ {int pages; double ntuples; int /*<<< orphan*/  filename; scalar_t__ is_program; } ;
struct TYPE_7__ {scalar_t__ pages; double tuples; double rows; int /*<<< orphan*/  baserestrictinfo; TYPE_1__* reltarget; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ FileFdwPlanState ;
typedef  int BlockNumber ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  JOIN_INNER ; 
 int MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeofHeapTupleHeader ; 
 double clamp_row_est (double) ; 
 double clauselist_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void
estimate_size(PlannerInfo *root, RelOptInfo *baserel,
			  FileFdwPlanState *fdw_private)
{
	struct stat stat_buf;
	BlockNumber pages;
	double		ntuples;
	double		nrows;

	/*
	 * Get size of the file.  It might not be there at plan time, though, in
	 * which case we have to use a default estimate.  We also have to fall
	 * back to the default if using a program as the input.
	 */
	if (fdw_private->is_program || stat(fdw_private->filename, &stat_buf) < 0)
		stat_buf.st_size = 10 * BLCKSZ;

	/*
	 * Convert size to pages for use in I/O cost estimate later.
	 */
	pages = (stat_buf.st_size + (BLCKSZ - 1)) / BLCKSZ;
	if (pages < 1)
		pages = 1;
	fdw_private->pages = pages;

	/*
	 * Estimate the number of tuples in the file.
	 */
	if (baserel->pages > 0)
	{
		/*
		 * We have # of pages and # of tuples from pg_class (that is, from a
		 * previous ANALYZE), so compute a tuples-per-page estimate and scale
		 * that by the current file size.
		 */
		double		density;

		density = baserel->tuples / (double) baserel->pages;
		ntuples = clamp_row_est(density * (double) pages);
	}
	else
	{
		/*
		 * Otherwise we have to fake it.  We back into this estimate using the
		 * planner's idea of the relation width; which is bogus if not all
		 * columns are being read, not to mention that the text representation
		 * of a row probably isn't the same size as its internal
		 * representation.  Possibly we could do something better, but the
		 * real answer to anyone who complains is "ANALYZE" ...
		 */
		int			tuple_width;

		tuple_width = MAXALIGN(baserel->reltarget->width) +
			MAXALIGN(SizeofHeapTupleHeader);
		ntuples = clamp_row_est((double) stat_buf.st_size /
								(double) tuple_width);
	}
	fdw_private->ntuples = ntuples;

	/*
	 * Now estimate the number of rows returned by the scan after applying the
	 * baserestrictinfo quals.
	 */
	nrows = ntuples *
		clauselist_selectivity(root,
							   baserel->baserestrictinfo,
							   0,
							   JOIN_INNER,
							   NULL);

	nrows = clamp_row_est(nrows);

	/* Save the output-rows estimate for the planner */
	baserel->rows = nrows;
}