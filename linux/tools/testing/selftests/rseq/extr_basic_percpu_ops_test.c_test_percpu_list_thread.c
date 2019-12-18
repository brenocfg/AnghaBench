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
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ rseq_register_current_thread () ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 struct percpu_list_node* this_cpu_list_pop (struct percpu_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_list_push (struct percpu_list*,struct percpu_list_node*,int /*<<< orphan*/ *) ; 

void *test_percpu_list_thread(void *arg)
{
	int i;
	struct percpu_list *list = (struct percpu_list *)arg;

	if (rseq_register_current_thread()) {
		fprintf(stderr, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		abort();
	}

	for (i = 0; i < 100000; i++) {
		struct percpu_list_node *node;

		node = this_cpu_list_pop(list, NULL);
		sched_yield();  /* encourage shuffling */
		if (node)
			this_cpu_list_push(list, node, NULL);
	}

	if (rseq_unregister_current_thread()) {
		fprintf(stderr, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		abort();
	}

	return NULL;
}