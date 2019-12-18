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
struct evsel {void* handler; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct evsel*) ; 
 int /*<<< orphan*/  evlist__add (struct evlist*,struct evsel*) ; 
 struct evsel* perf_evsel__newtp (char const*,char const*) ; 

int perf_evlist__add_newtp(struct evlist *evlist,
			   const char *sys, const char *name, void *handler)
{
	struct evsel *evsel = perf_evsel__newtp(sys, name);

	if (IS_ERR(evsel))
		return -1;

	evsel->handler = handler;
	evlist__add(evlist, evsel);
	return 0;
}