#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_map_event {unsigned int nr; TYPE_2__* entries; } ;
struct thread_map {int nr; int /*<<< orphan*/  refcnt; TYPE_1__* map; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  comm; scalar_t__ pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strndup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_map__set_pid (struct thread_map*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_map__copy_event(struct thread_map *threads,
				   struct thread_map_event *event)
{
	unsigned i;

	threads->nr = (int) event->nr;

	for (i = 0; i < event->nr; i++) {
		thread_map__set_pid(threads, i, (pid_t) event->entries[i].pid);
		threads->map[i].comm = strndup(event->entries[i].comm, 16);
	}

	refcount_set(&threads->refcnt, 1);
}