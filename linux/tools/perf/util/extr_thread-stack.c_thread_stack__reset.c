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
struct thread_stack {unsigned int arr_sz; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__free (struct thread*,struct thread_stack*) ; 
 int /*<<< orphan*/  memset (struct thread_stack*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void thread_stack__reset(struct thread *thread, struct thread_stack *ts)
{
	unsigned int arr_sz = ts->arr_sz;

	__thread_stack__free(thread, ts);
	memset(ts, 0, sizeof(*ts));
	ts->arr_sz = arr_sz;
}