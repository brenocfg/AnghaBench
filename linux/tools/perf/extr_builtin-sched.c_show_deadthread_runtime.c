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
struct thread {int /*<<< orphan*/  dead; } ;

/* Variables and functions */
 int __show_thread_runtime (struct thread*,void*) ; 

__attribute__((used)) static int show_deadthread_runtime(struct thread *t, void *priv)
{
	if (!t->dead)
		return 0;

	return __show_thread_runtime(t, priv);
}