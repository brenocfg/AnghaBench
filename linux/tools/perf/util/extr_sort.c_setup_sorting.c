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
struct evlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ SORT_MODE__DIFF ; 
 int __setup_output_field () ; 
 int __setup_sorting (struct evlist*) ; 
 scalar_t__ default_parent_pattern ; 
 scalar_t__ parent_pattern ; 
 int /*<<< orphan*/  perf_hpp__append_sort_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_hpp__init () ; 
 scalar_t__ perf_hpp__setup_hists_formats (int /*<<< orphan*/ *,struct evlist*) ; 
 int /*<<< orphan*/  perf_hpp__setup_output_field (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_hpp_list ; 
 int /*<<< orphan*/  reset_dimensions () ; 
 scalar_t__ sort__mode ; 
 int sort_dimension__add (int /*<<< orphan*/ *,char*,struct evlist*,int) ; 

int setup_sorting(struct evlist *evlist)
{
	int err;

	err = __setup_sorting(evlist);
	if (err < 0)
		return err;

	if (parent_pattern != default_parent_pattern) {
		err = sort_dimension__add(&perf_hpp_list, "parent", evlist, -1);
		if (err < 0)
			return err;
	}

	reset_dimensions();

	/*
	 * perf diff doesn't use default hpp output fields.
	 */
	if (sort__mode != SORT_MODE__DIFF)
		perf_hpp__init();

	err = __setup_output_field();
	if (err < 0)
		return err;

	/* copy sort keys to output fields */
	perf_hpp__setup_output_field(&perf_hpp_list);
	/* and then copy output fields to sort keys */
	perf_hpp__append_sort_keys(&perf_hpp_list);

	/* setup hists-specific output fields */
	if (perf_hpp__setup_hists_formats(&perf_hpp_list, evlist) < 0)
		return -1;

	return 0;
}