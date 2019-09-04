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
typedef  int /*<<< orphan*/  kmem_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void
kmem_zone_free(kmem_zone_t *zone, void *ptr)
{
	kmem_cache_free(zone, ptr);
}