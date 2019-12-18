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
struct kmem_cache {int flags; int /*<<< orphan*/  red_left_pad; } ;

/* Variables and functions */
 int SLAB_RED_ZONE ; 
 scalar_t__ kmem_cache_debug (struct kmem_cache*) ; 

void *fixup_red_left(struct kmem_cache *s, void *p)
{
	if (kmem_cache_debug(s) && s->flags & SLAB_RED_ZONE)
		p += s->red_left_pad;

	return p;
}