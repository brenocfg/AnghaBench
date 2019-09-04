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
struct thread_map_event {int /*<<< orphan*/  nr; } ;
struct thread_map {int dummy; } ;

/* Variables and functions */
 struct thread_map* thread_map__alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_map__copy_event (struct thread_map*,struct thread_map_event*) ; 

struct thread_map *thread_map__new_event(struct thread_map_event *event)
{
	struct thread_map *threads;

	threads = thread_map__alloc(event->nr);
	if (threads)
		thread_map__copy_event(threads, event);

	return threads;
}