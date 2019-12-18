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
struct evsel {char* filter; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char const*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int perf_evsel__set_filter (struct evsel*,char const*) ; 

__attribute__((used)) static int perf_evsel__append_filter(struct evsel *evsel,
				     const char *fmt, const char *filter)
{
	char *new_filter;

	if (evsel->filter == NULL)
		return perf_evsel__set_filter(evsel, filter);

	if (asprintf(&new_filter, fmt, evsel->filter, filter) > 0) {
		free(evsel->filter);
		evsel->filter = new_filter;
		return 0;
	}

	return -1;
}