#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t object_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void const* ZERO_SIZE_PTR ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* virt_to_cache (void const*) ; 

size_t ksize(const void *objp)
{
	size_t size;

	BUG_ON(!objp);
	if (unlikely(objp == ZERO_SIZE_PTR))
		return 0;

	size = virt_to_cache(objp)->object_size;
	/* We assume that ksize callers could use the whole allocated area,
	 * so we need to unpoison this area.
	 */
	kasan_unpoison_shadow(objp, size);

	return size;
}