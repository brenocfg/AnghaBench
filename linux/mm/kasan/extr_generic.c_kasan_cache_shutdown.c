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
 int /*<<< orphan*/  __kmem_cache_empty (struct kmem_cache*) ; 
 int /*<<< orphan*/  quarantine_remove_cache (struct kmem_cache*) ; 

void kasan_cache_shutdown(struct kmem_cache *cache)
{
	if (!__kmem_cache_empty(cache))
		quarantine_remove_cache(cache);
}