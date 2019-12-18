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
struct TYPE_5__ {TYPE_1__* rd_rel; } ;
struct TYPE_4__ {double relpages; double reltuples; } ;
typedef  TYPE_2__* Relation ;
typedef  double BlockNumber ;

/* Variables and functions */
 double floor (double) ; 

double
vac_estimate_reltuples(Relation relation,
					   BlockNumber total_pages,
					   BlockNumber scanned_pages,
					   double scanned_tuples)
{
	BlockNumber old_rel_pages = relation->rd_rel->relpages;
	double		old_rel_tuples = relation->rd_rel->reltuples;
	double		old_density;
	double		unscanned_pages;
	double		total_tuples;

	/* If we did scan the whole table, just use the count as-is */
	if (scanned_pages >= total_pages)
		return scanned_tuples;

	/*
	 * If scanned_pages is zero but total_pages isn't, keep the existing value
	 * of reltuples.  (Note: callers should avoid updating the pg_class
	 * statistics in this situation, since no new information has been
	 * provided.)
	 */
	if (scanned_pages == 0)
		return old_rel_tuples;

	/*
	 * If old value of relpages is zero, old density is indeterminate; we
	 * can't do much except scale up scanned_tuples to match total_pages.
	 */
	if (old_rel_pages == 0)
		return floor((scanned_tuples / scanned_pages) * total_pages + 0.5);

	/*
	 * Okay, we've covered the corner cases.  The normal calculation is to
	 * convert the old measurement to a density (tuples per page), then
	 * estimate the number of tuples in the unscanned pages using that figure,
	 * and finally add on the number of tuples in the scanned pages.
	 */
	old_density = old_rel_tuples / old_rel_pages;
	unscanned_pages = (double) total_pages - (double) scanned_pages;
	total_tuples = old_density * unscanned_pages + scanned_tuples;
	return floor(total_tuples + 0.5);
}