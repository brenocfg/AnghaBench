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
struct inet_frags {int /*<<< orphan*/ * frags_cachep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

void inet_frags_fini(struct inet_frags *f)
{
	/* We must wait that all inet_frag_destroy_rcu() have completed. */
	rcu_barrier();

	kmem_cache_destroy(f->frags_cachep);
	f->frags_cachep = NULL;
}