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
typedef  int /*<<< orphan*/  u64 ;
struct thread {int comm_set; int /*<<< orphan*/  mg; int /*<<< orphan*/  comm_list; } ;
struct comm {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct comm* comm__new (char const*,int /*<<< orphan*/ ,int) ; 
 int comm__override (struct comm*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct comm* thread__comm (struct thread*) ; 
 int /*<<< orphan*/  unwind__flush_access (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ____thread__set_comm(struct thread *thread, const char *str,
				u64 timestamp, bool exec)
{
	struct comm *new, *curr = thread__comm(thread);

	/* Override the default :tid entry */
	if (!thread->comm_set) {
		int err = comm__override(curr, str, timestamp, exec);
		if (err)
			return err;
	} else {
		new = comm__new(str, timestamp, exec);
		if (!new)
			return -ENOMEM;
		list_add(&new->list, &thread->comm_list);

		if (exec)
			unwind__flush_access(thread->mg);
	}

	thread->comm_set = true;

	return 0;
}