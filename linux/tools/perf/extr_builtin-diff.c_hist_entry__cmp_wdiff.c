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
struct perf_hpp_fmt {int dummy; } ;
struct hist_entry {int dummy; } ;
struct data__file {int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_WEIGHTED_DIFF ; 
 struct data__file* fmt_to_data_file (struct perf_hpp_fmt*) ; 
 int /*<<< orphan*/  hist_entry__cmp_compute (struct hist_entry*,struct hist_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
hist_entry__cmp_wdiff(struct perf_hpp_fmt *fmt,
		      struct hist_entry *left, struct hist_entry *right)
{
	struct data__file *d = fmt_to_data_file(fmt);

	return hist_entry__cmp_compute(right, left, COMPUTE_WEIGHTED_DIFF, d->idx);
}