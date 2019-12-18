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
struct TYPE_2__ {int done; int /*<<< orphan*/  th; } ;
struct evlist {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  evlist__delete (struct evlist*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void perf_evlist__stop_sb_thread(struct evlist *evlist)
{
	if (!evlist)
		return;
	evlist->thread.done = 1;
	pthread_join(evlist->thread.th, NULL);
	evlist__delete(evlist);
}