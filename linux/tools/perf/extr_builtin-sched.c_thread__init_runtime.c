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
struct thread_runtime {int /*<<< orphan*/  run_stats; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread__set_priv (struct thread*,struct thread_runtime*) ; 
 struct thread_runtime* zalloc (int) ; 

__attribute__((used)) static struct thread_runtime *thread__init_runtime(struct thread *thread)
{
	struct thread_runtime *r;

	r = zalloc(sizeof(struct thread_runtime));
	if (!r)
		return NULL;

	init_stats(&r->run_stats);
	thread__set_priv(thread, r);

	return r;
}