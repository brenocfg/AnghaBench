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
struct qlist_node {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SLAB ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 int /*<<< orphan*/  ___cache_free (struct kmem_cache*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 void* qlink_to_object (struct qlist_node*,struct kmem_cache*) ; 

__attribute__((used)) static void qlink_free(struct qlist_node *qlink, struct kmem_cache *cache)
{
	void *object = qlink_to_object(qlink, cache);
	unsigned long flags;

	if (IS_ENABLED(CONFIG_SLAB))
		local_irq_save(flags);

	___cache_free(cache, object, _THIS_IP_);

	if (IS_ENABLED(CONFIG_SLAB))
		local_irq_restore(flags);
}