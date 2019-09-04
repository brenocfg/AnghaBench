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
struct rsi_thread {int /*<<< orphan*/  task; int /*<<< orphan*/  event; int /*<<< orphan*/  thread_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_set_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rsi_kill_thread(struct rsi_thread *handle)
{
	atomic_inc(&handle->thread_done);
	rsi_set_event(&handle->event);

	return kthread_stop(handle->task);
}