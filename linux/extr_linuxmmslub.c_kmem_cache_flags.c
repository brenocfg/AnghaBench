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
typedef  int /*<<< orphan*/  slab_flags_t ;

/* Variables and functions */

slab_flags_t kmem_cache_flags(unsigned int object_size,
	slab_flags_t flags, const char *name,
	void (*ctor)(void *))
{
	return flags;
}