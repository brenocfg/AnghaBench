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
struct perf_event {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  _free_event (struct perf_event*) ; 
 int atomic_long_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_event(struct perf_event *event)
{
	if (WARN(atomic_long_cmpxchg(&event->refcount, 1, 0) != 1,
				"unexpected event refcount: %ld; ptr=%p\n",
				atomic_long_read(&event->refcount), event)) {
		/* leak to avoid use-after-free */
		return;
	}

	_free_event(event);
}