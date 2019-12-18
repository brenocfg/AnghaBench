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
 int /*<<< orphan*/  mt_tree ; 
 int /*<<< orphan*/  obj1 ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  worker_barrier ; 

__attribute__((used)) static void *writer_fn(void *arg)
{
	int i;

	rcu_register_thread();
	pthread_barrier_wait(&worker_barrier);

	for (i = 0; i < 1000000; i++) {
		radix_tree_insert(&mt_tree, 1, &obj1);
		radix_tree_delete(&mt_tree, 1);
	}

	rcu_unregister_thread();

	return NULL;
}