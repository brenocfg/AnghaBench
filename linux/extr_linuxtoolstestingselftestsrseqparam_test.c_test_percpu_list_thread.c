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
struct percpu_list_node {int dummy; } ;
struct percpu_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ gettid () ; 
 int /*<<< orphan*/  nr_abort ; 
 int /*<<< orphan*/  opt_disable_rseq ; 
 long long opt_reps ; 
 scalar_t__ opt_yield ; 
 int /*<<< orphan*/  printf_verbose (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rseq_register_current_thread () ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  signals_delivered ; 
 struct percpu_list_node* this_cpu_list_pop (struct percpu_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_list_push (struct percpu_list*,struct percpu_list_node*,int /*<<< orphan*/ *) ; 

void *test_percpu_list_thread(void *arg)
{
	long long i, reps;
	struct percpu_list *list = (struct percpu_list *)arg;

	if (!opt_disable_rseq && rseq_register_current_thread())
		abort();

	reps = opt_reps;
	for (i = 0; i < reps; i++) {
		struct percpu_list_node *node;

		node = this_cpu_list_pop(list, NULL);
		if (opt_yield)
			sched_yield();  /* encourage shuffling */
		if (node)
			this_cpu_list_push(list, node, NULL);
	}

	printf_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (int) gettid(), nr_abort, signals_delivered);
	if (!opt_disable_rseq && rseq_unregister_current_thread())
		abort();

	return NULL;
}