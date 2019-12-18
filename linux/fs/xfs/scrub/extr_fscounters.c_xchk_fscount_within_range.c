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
typedef  scalar_t__ uint64_t ;
struct xfs_scrub {int /*<<< orphan*/  mp; } ;
struct percpu_counter {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ XCHK_FSCOUNT_MIN_VARIANCE ; 
 scalar_t__ max (scalar_t__ const,scalar_t__) ; 
 scalar_t__ min (scalar_t__ const,scalar_t__) ; 
 scalar_t__ percpu_counter_sum (struct percpu_counter*) ; 
 int /*<<< orphan*/  trace_xchk_fscounters_within_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  xchk_set_incomplete (struct xfs_scrub*) ; 

__attribute__((used)) static inline bool
xchk_fscount_within_range(
	struct xfs_scrub	*sc,
	const int64_t		old_value,
	struct percpu_counter	*counter,
	uint64_t		expected)
{
	int64_t			min_value, max_value;
	int64_t			curr_value = percpu_counter_sum(counter);

	trace_xchk_fscounters_within_range(sc->mp, expected, curr_value,
			old_value);

	/* Negative values are always wrong. */
	if (curr_value < 0)
		return false;

	/* Exact matches are always ok. */
	if (curr_value == expected)
		return true;

	min_value = min(old_value, curr_value);
	max_value = max(old_value, curr_value);

	/* Within the before-and-after range is ok. */
	if (expected >= min_value && expected <= max_value)
		return true;

	/*
	 * If the difference between the two summations is too large, the fs
	 * might just be busy and so we'll mark the scrub incomplete.  Return
	 * true here so that we don't mark the counter corrupt.
	 *
	 * XXX: In the future when userspace can grant scrub permission to
	 * quiesce the filesystem to solve the outsized variance problem, this
	 * check should be moved up and the return code changed to signal to
	 * userspace that we need quiesce permission.
	 */
	if (max_value - min_value >= XCHK_FSCOUNT_MIN_VARIANCE) {
		xchk_set_incomplete(sc);
		return true;
	}

	return false;
}