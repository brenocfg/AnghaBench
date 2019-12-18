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
struct thread_runtime {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct thread_runtime* thread__init_runtime (struct thread*) ; 
 struct thread_runtime* thread__priv (struct thread*) ; 

__attribute__((used)) static struct thread_runtime *thread__get_runtime(struct thread *thread)
{
	struct thread_runtime *tr;

	tr = thread__priv(thread);
	if (tr == NULL) {
		tr = thread__init_runtime(thread);
		if (tr == NULL)
			pr_debug("Failed to malloc memory for runtime data.\n");
	}

	return tr;
}