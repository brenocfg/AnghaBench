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
struct kmem_cache_cpu {int /*<<< orphan*/  tid; int /*<<< orphan*/  freelist; int /*<<< orphan*/  page; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSLAB_FLUSH ; 
 int /*<<< orphan*/  deactivate_slab (struct kmem_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kmem_cache_cpu*) ; 
 int /*<<< orphan*/  next_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void flush_slab(struct kmem_cache *s, struct kmem_cache_cpu *c)
{
	stat(s, CPUSLAB_FLUSH);
	deactivate_slab(s, c->page, c->freelist, c);

	c->tid = next_tid(c->tid);
}