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
struct slob_rcu {int dummy; } ;
struct kmem_cache {int size; int flags; } ;
typedef  int slab_flags_t ;

/* Variables and functions */
 int SLAB_TYPESAFE_BY_RCU ; 

int __kmem_cache_create(struct kmem_cache *c, slab_flags_t flags)
{
	if (flags & SLAB_TYPESAFE_BY_RCU) {
		/* leave room for rcu footer at the end of object */
		c->size += sizeof(struct slob_rcu);
	}
	c->flags = flags;
	return 0;
}