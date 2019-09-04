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

/* Variables and functions */
 int __kmem_cache_shrink (struct kmem_cache*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  get_online_mems () ; 
 int /*<<< orphan*/  kasan_cache_shrink (struct kmem_cache*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  put_online_mems () ; 

int kmem_cache_shrink(struct kmem_cache *cachep)
{
	int ret;

	get_online_cpus();
	get_online_mems();
	kasan_cache_shrink(cachep);
	ret = __kmem_cache_shrink(cachep);
	put_online_mems();
	put_online_cpus();
	return ret;
}