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
struct page {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  find_get_pages (int /*<<< orphan*/ ,int,struct page**) ; 
 int /*<<< orphan*/  mt_lock ; 
 int /*<<< orphan*/  mt_tree ; 
 struct page* page_alloc () ; 
 int /*<<< orphan*/  page_free (struct page*) ; 
 scalar_t__ pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct page* radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,struct page*) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  worker_barrier ; 

__attribute__((used)) static void *regression1_fn(void *arg)
{
	rcu_register_thread();

	if (pthread_barrier_wait(&worker_barrier) ==
			PTHREAD_BARRIER_SERIAL_THREAD) {
		int j;

		for (j = 0; j < 1000000; j++) {
			struct page *p;

			p = page_alloc();
			pthread_mutex_lock(&mt_lock);
			radix_tree_insert(&mt_tree, 0, p);
			pthread_mutex_unlock(&mt_lock);

			p = page_alloc();
			pthread_mutex_lock(&mt_lock);
			radix_tree_insert(&mt_tree, 1, p);
			pthread_mutex_unlock(&mt_lock);

			pthread_mutex_lock(&mt_lock);
			p = radix_tree_delete(&mt_tree, 1);
			pthread_mutex_lock(&p->lock);
			p->count--;
			pthread_mutex_unlock(&p->lock);
			pthread_mutex_unlock(&mt_lock);
			page_free(p);

			pthread_mutex_lock(&mt_lock);
			p = radix_tree_delete(&mt_tree, 0);
			pthread_mutex_lock(&p->lock);
			p->count--;
			pthread_mutex_unlock(&p->lock);
			pthread_mutex_unlock(&mt_lock);
			page_free(p);
		}
	} else {
		int j;

		for (j = 0; j < 100000000; j++) {
			struct page *pages[10];

			find_get_pages(0, 10, pages);
		}
	}

	rcu_unregister_thread();

	return NULL;
}