#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  MAX_IO_CONCURRENCY ; 
 int /*<<< orphan*/  Max (int,int /*<<< orphan*/ ) ; 
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ComputeIoConcurrency(int io_concurrency, double *target)
{
	double		new_prefetch_pages = 0.0;
	int			i;

	/*
	 * Make sure the io_concurrency value is within valid range; it may have
	 * been forced with a manual pg_tablespace update.
	 */
	io_concurrency = Min(Max(io_concurrency, 0), MAX_IO_CONCURRENCY);

	/*----------
	 * The user-visible GUC parameter is the number of drives (spindles),
	 * which we need to translate to a number-of-pages-to-prefetch target.
	 * The target value is stashed in *extra and then assigned to the actual
	 * variable by assign_effective_io_concurrency.
	 *
	 * The expected number of prefetch pages needed to keep N drives busy is:
	 *
	 * drives |   I/O requests
	 * -------+----------------
	 *		1 |   1
	 *		2 |   2/1 + 2/2 = 3
	 *		3 |   3/1 + 3/2 + 3/3 = 5 1/2
	 *		4 |   4/1 + 4/2 + 4/3 + 4/4 = 8 1/3
	 *		n |   n * H(n)
	 *
	 * This is called the "coupon collector problem" and H(n) is called the
	 * harmonic series.  This could be approximated by n * ln(n), but for
	 * reasonable numbers of drives we might as well just compute the series.
	 *
	 * Alternatively we could set the target to the number of pages necessary
	 * so that the expected number of active spindles is some arbitrary
	 * percentage of the total.  This sounds the same but is actually slightly
	 * different.  The result ends up being ln(1-P)/ln((n-1)/n) where P is
	 * that desired fraction.
	 *
	 * Experimental results show that both of these formulas aren't aggressive
	 * enough, but we don't really have any better proposals.
	 *
	 * Note that if io_concurrency = 0 (disabled), we must set target = 0.
	 *----------
	 */

	for (i = 1; i <= io_concurrency; i++)
		new_prefetch_pages += (double) io_concurrency / (double) i;

	*target = new_prefetch_pages;

	/* This range check shouldn't fail, but let's be paranoid */
	return (new_prefetch_pages >= 0.0 && new_prefetch_pages < (double) INT_MAX);
}