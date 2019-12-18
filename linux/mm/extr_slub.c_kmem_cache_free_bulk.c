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
struct kmem_cache {int dummy; } ;
struct detached_freelist {int /*<<< orphan*/  cnt; int /*<<< orphan*/  tail; int /*<<< orphan*/  freelist; int /*<<< orphan*/  page; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 size_t build_detached_freelist (struct kmem_cache*,size_t,void**,struct detached_freelist*) ; 
 scalar_t__ likely (size_t) ; 
 int /*<<< orphan*/  slab_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kmem_cache_free_bulk(struct kmem_cache *s, size_t size, void **p)
{
	if (WARN_ON(!size))
		return;

	do {
		struct detached_freelist df;

		size = build_detached_freelist(s, size, p, &df);
		if (!df.page)
			continue;

		slab_free(df.s, df.page, df.freelist, df.tail, df.cnt,_RET_IP_);
	} while (likely(size));
}