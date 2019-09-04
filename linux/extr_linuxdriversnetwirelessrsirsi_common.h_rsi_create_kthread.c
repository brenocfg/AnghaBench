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
typedef  int /*<<< orphan*/  u8 ;
struct rsi_thread {int /*<<< orphan*/  task; int /*<<< orphan*/  thread_done; int /*<<< orphan*/  completion; } ;
struct rsi_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (void*,struct rsi_common*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rsi_create_kthread(struct rsi_common *common,
				     struct rsi_thread *thread,
				     void *func_ptr,
				     u8 *name)
{
	init_completion(&thread->completion);
	atomic_set(&thread->thread_done, 0);
	thread->task = kthread_run(func_ptr, common, "%s", name);
	if (IS_ERR(thread->task))
		return (int)PTR_ERR(thread->task);

	return 0;
}