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
struct radix_tree_node {struct radix_tree_node* parent; } ;
struct kmem_cache {int nr_objs; int /*<<< orphan*/  lock; struct radix_tree_node* objs; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  POISON_FREE ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ kmalloc_verbose ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uatomic_dec (int /*<<< orphan*/ *) ; 

void kmem_cache_free(struct kmem_cache *cachep, void *objp)
{
	assert(objp);
	uatomic_dec(&nr_allocated);
	if (kmalloc_verbose)
		printf("Freeing %p to slab\n", objp);
	pthread_mutex_lock(&cachep->lock);
	if (cachep->nr_objs > 10) {
		memset(objp, POISON_FREE, cachep->size);
		free(objp);
	} else {
		struct radix_tree_node *node = objp;
		cachep->nr_objs++;
		node->parent = cachep->objs;
		cachep->objs = node;
	}
	pthread_mutex_unlock(&cachep->lock);
}