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
typedef  union perf_event {int dummy; } perf_event ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evlist__delete (struct evlist*) ; 
 int process_event (struct evlist**,union perf_event*) ; 

__attribute__((used)) static int process_events(union perf_event **events, size_t count)
{
	struct evlist *evlist = NULL;
	int err = 0;
	size_t i;

	for (i = 0; i < count && !err; i++)
		err = process_event(&evlist, events[i]);

	evlist__delete(evlist);

	return err;
}