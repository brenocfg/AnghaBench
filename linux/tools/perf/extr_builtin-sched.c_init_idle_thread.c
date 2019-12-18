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
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  run_stats; } ;
struct idle_thread_runtime {int /*<<< orphan*/  cursor; int /*<<< orphan*/  callchain; TYPE_1__ tr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  callchain_cursor_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_comm ; 
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread__set_comm (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__set_priv (struct thread*,struct idle_thread_runtime*) ; 
 struct idle_thread_runtime* zalloc (int) ; 

__attribute__((used)) static int init_idle_thread(struct thread *thread)
{
	struct idle_thread_runtime *itr;

	thread__set_comm(thread, idle_comm, 0);

	itr = zalloc(sizeof(*itr));
	if (itr == NULL)
		return -ENOMEM;

	init_stats(&itr->tr.run_stats);
	callchain_init(&itr->callchain);
	callchain_cursor_reset(&itr->cursor);
	thread__set_priv(thread, itr);

	return 0;
}