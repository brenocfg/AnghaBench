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
struct ftrace_branch_data {scalar_t__ incorrect; scalar_t__ correct; } ;

/* Variables and functions */
 long get_incorrect_percent (struct ftrace_branch_data*) ; 

__attribute__((used)) static int annotated_branch_stat_cmp(void *p1, void *p2)
{
	struct ftrace_branch_data *a = p1;
	struct ftrace_branch_data *b = p2;

	long percent_a, percent_b;

	percent_a = get_incorrect_percent(a);
	percent_b = get_incorrect_percent(b);

	if (percent_a < percent_b)
		return -1;
	if (percent_a > percent_b)
		return 1;

	if (a->incorrect < b->incorrect)
		return -1;
	if (a->incorrect > b->incorrect)
		return 1;

	/*
	 * Since the above shows worse (incorrect) cases
	 * first, we continue that by showing best (correct)
	 * cases last.
	 */
	if (a->correct > b->correct)
		return -1;
	if (a->correct < b->correct)
		return 1;

	return 0;
}