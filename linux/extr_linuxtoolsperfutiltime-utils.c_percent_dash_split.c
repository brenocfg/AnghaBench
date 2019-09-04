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
typedef  double u64 ;
struct perf_time_interval {double start; double end; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ parse_percent (double*,char*) ; 
 double round (double) ; 
 int split_start_end (char**,char**,char*,char) ; 

__attribute__((used)) static int percent_dash_split(char *str, struct perf_time_interval *ptime,
			      u64 start, u64 end)
{
	char *start_str = NULL, *end_str;
	double start_pcnt, end_pcnt;
	u64 total = end - start;
	int ret;

	/*
	 * Example: 0%-10%
	 */

	ret = split_start_end(&start_str, &end_str, str, '-');
	if (ret || !start_str)
		return ret;

	if ((parse_percent(&start_pcnt, start_str) != 0) ||
	    (parse_percent(&end_pcnt, end_str) != 0)) {
		free(start_str);
		return -1;
	}

	free(start_str);

	if (start_pcnt < 0.0 || start_pcnt > 1.0 ||
	    end_pcnt < 0.0 || end_pcnt > 1.0 ||
	    start_pcnt > end_pcnt) {
		return -1;
	}

	ptime->start = start + round(start_pcnt * total);
	ptime->end = start + round(end_pcnt * total);

	return 0;
}