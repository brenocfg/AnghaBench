#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_hpp_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_LIST (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2c_hists__init_output ; 
 int /*<<< orphan*/  c2c_hists__init_sort ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* hists ; 
 int /*<<< orphan*/  perf_hpp__append_sort_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_hpp__setup_output_field (struct perf_hpp_list*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int hpp_list__parse(struct perf_hpp_list *hpp_list,
			   const char *output_,
			   const char *sort_)
{
	char *output = output_ ? strdup(output_) : NULL;
	char *sort   = sort_   ? strdup(sort_) : NULL;
	int ret;

	PARSE_LIST(output, c2c_hists__init_output);
	PARSE_LIST(sort,   c2c_hists__init_sort);

	/* copy sort keys to output fields */
	perf_hpp__setup_output_field(hpp_list);

	/*
	 * We dont need other sorting keys other than those
	 * we already specified. It also really slows down
	 * the processing a lot with big number of output
	 * fields, so switching this off for c2c.
	 */

#if 0
	/* and then copy output fields to sort keys */
	perf_hpp__append_sort_keys(&hists->list);
#endif

	free(output);
	free(sort);
	return ret;
}