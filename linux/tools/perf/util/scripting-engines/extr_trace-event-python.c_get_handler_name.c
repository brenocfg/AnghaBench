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
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void get_handler_name(char *str, size_t size,
			     struct evsel *evsel)
{
	char *p = str;

	scnprintf(str, size, "stat__%s", perf_evsel__name(evsel));

	while ((p = strchr(p, ':'))) {
		*p = '_';
		p++;
	}
}