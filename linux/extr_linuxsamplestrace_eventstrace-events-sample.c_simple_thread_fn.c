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

/* Variables and functions */
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  simple_thread_func_fn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simple_thread_fn(void *arg)
{
	int cnt = 0;

	while (!kthread_should_stop())
		simple_thread_func_fn(cnt++);

	return 0;
}