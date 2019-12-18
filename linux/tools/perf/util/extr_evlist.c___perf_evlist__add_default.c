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
struct evlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  evlist__add (struct evlist*,struct evsel*) ; 
 struct evsel* perf_evsel__new_cycles (int) ; 

int __perf_evlist__add_default(struct evlist *evlist, bool precise)
{
	struct evsel *evsel = perf_evsel__new_cycles(precise);

	if (evsel == NULL)
		return -ENOMEM;

	evlist__add(evlist, evsel);
	return 0;
}