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
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

int perf_evsel__set_filter(struct evsel *evsel, const char *filter)
{
	char *new_filter = strdup(filter);

	if (new_filter != NULL) {
		free(evsel->filter);
		evsel->filter = new_filter;
		return 0;
	}

	return -1;
}