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
 int /*<<< orphan*/  evlist__delete (struct evlist*) ; 
 struct evlist* evlist__new () ; 
 scalar_t__ perf_evlist__add_dummy (struct evlist*) ; 

struct evlist *perf_evlist__new_dummy(void)
{
	struct evlist *evlist = evlist__new();

	if (evlist && perf_evlist__add_dummy(evlist)) {
		evlist__delete(evlist);
		evlist = NULL;
	}

	return evlist;
}