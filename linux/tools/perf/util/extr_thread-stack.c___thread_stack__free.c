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
struct thread_stack {int /*<<< orphan*/  stack; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__flush (struct thread*,struct thread_stack*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __thread_stack__free(struct thread *thread, struct thread_stack *ts)
{
	__thread_stack__flush(thread, ts);
	zfree(&ts->stack);
}