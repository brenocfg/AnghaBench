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
 char* perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *fixunit(char *buf, struct evsel *evsel,
			   const char *unit)
{
	if (!strncmp(unit, "of all", 6)) {
		snprintf(buf, 1024, "%s %s", perf_evsel__name(evsel),
			 unit);
		return buf;
	}
	return unit;
}