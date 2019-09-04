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
typedef  scalar_t__ u64 ;
struct thread {int /*<<< orphan*/  namespaces_list; } ;
struct namespaces_event {int dummy; } ;
struct namespaces {scalar_t__ end_time; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct namespaces* list_next_entry (struct namespaces*,int /*<<< orphan*/ ) ; 
 struct namespaces* namespaces__new (struct namespaces_event*) ; 
 struct namespaces* thread__namespaces (struct thread*) ; 

__attribute__((used)) static int __thread__set_namespaces(struct thread *thread, u64 timestamp,
				    struct namespaces_event *event)
{
	struct namespaces *new, *curr = thread__namespaces(thread);

	new = namespaces__new(event);
	if (!new)
		return -ENOMEM;

	list_add(&new->list, &thread->namespaces_list);

	if (timestamp && curr) {
		/*
		 * setns syscall must have changed few or all the namespaces
		 * of this thread. Update end time for the namespaces
		 * previously used.
		 */
		curr = list_next_entry(new, list);
		curr->end_time = timestamp;
	}

	return 0;
}