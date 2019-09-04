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

__attribute__((used)) static inline bool kmem_cache_has_cpu_partial(struct kmem_cache *s)
{
#ifdef CONFIG_SLUB_CPU_PARTIAL
	return !kmem_cache_debug(s);
#else
	return false;
#endif
}