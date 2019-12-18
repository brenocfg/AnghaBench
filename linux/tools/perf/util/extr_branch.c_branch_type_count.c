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
typedef  scalar_t__ u64 ;
struct branch_type_stat {int /*<<< orphan*/  cross_4k; int /*<<< orphan*/  cross_2m; int /*<<< orphan*/  cond_bwd; int /*<<< orphan*/  cond_fwd; int /*<<< orphan*/ * counts; } ;
struct branch_flags {size_t type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AREA_2M ; 
 int /*<<< orphan*/  AREA_4K ; 
 size_t PERF_BR_COND ; 
 size_t PERF_BR_UNKNOWN ; 
 scalar_t__ cross_area (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void branch_type_count(struct branch_type_stat *st, struct branch_flags *flags,
		       u64 from, u64 to)
{
	if (flags->type == PERF_BR_UNKNOWN || from == 0)
		return;

	st->counts[flags->type]++;

	if (flags->type == PERF_BR_COND) {
		if (to > from)
			st->cond_fwd++;
		else
			st->cond_bwd++;
	}

	if (cross_area(from, to, AREA_2M))
		st->cross_2m++;
	else if (cross_area(from, to, AREA_4K))
		st->cross_4k++;
}