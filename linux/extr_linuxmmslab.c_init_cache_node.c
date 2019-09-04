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
struct kmem_cache_node {scalar_t__ free_limit; scalar_t__ next_reap; int /*<<< orphan*/  list_lock; } ;
struct kmem_cache {int batchcount; struct kmem_cache_node** node; scalar_t__ num; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long REAPTIMEOUT_NODE ; 
 struct kmem_cache_node* get_node (struct kmem_cache*,int) ; 
 scalar_t__ jiffies ; 
 struct kmem_cache_node* kmalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_node_init (struct kmem_cache_node*) ; 
 int nr_cpus_node (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_cache_node(struct kmem_cache *cachep, int node, gfp_t gfp)
{
	struct kmem_cache_node *n;

	/*
	 * Set up the kmem_cache_node for cpu before we can
	 * begin anything. Make sure some other cpu on this
	 * node has not already allocated this
	 */
	n = get_node(cachep, node);
	if (n) {
		spin_lock_irq(&n->list_lock);
		n->free_limit = (1 + nr_cpus_node(node)) * cachep->batchcount +
				cachep->num;
		spin_unlock_irq(&n->list_lock);

		return 0;
	}

	n = kmalloc_node(sizeof(struct kmem_cache_node), gfp, node);
	if (!n)
		return -ENOMEM;

	kmem_cache_node_init(n);
	n->next_reap = jiffies + REAPTIMEOUT_NODE +
		    ((unsigned long)cachep) % REAPTIMEOUT_NODE;

	n->free_limit =
		(1 + nr_cpus_node(node)) * cachep->batchcount + cachep->num;

	/*
	 * The kmem_cache_nodes don't come and go as CPUs
	 * come and go.  slab_mutex is sufficient
	 * protection here.
	 */
	cachep->node[node] = n;

	return 0;
}