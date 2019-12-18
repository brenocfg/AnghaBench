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

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 void const* ZERO_SIZE_PTR ; 
 int /*<<< orphan*/  __kasan_check_read (void const*,int) ; 
 size_t __ksize (void const*) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

size_t ksize(const void *objp)
{
	size_t size;

	if (WARN_ON_ONCE(!objp))
		return 0;
	/*
	 * We need to check that the pointed to object is valid, and only then
	 * unpoison the shadow memory below. We use __kasan_check_read(), to
	 * generate a more useful report at the time ksize() is called (rather
	 * than later where behaviour is undefined due to potential
	 * use-after-free or double-free).
	 *
	 * If the pointed to memory is invalid we return 0, to avoid users of
	 * ksize() writing to and potentially corrupting the memory region.
	 *
	 * We want to perform the check before __ksize(), to avoid potentially
	 * crashing in __ksize() due to accessing invalid metadata.
	 */
	if (unlikely(objp == ZERO_SIZE_PTR) || !__kasan_check_read(objp, 1))
		return 0;

	size = __ksize(objp);
	/*
	 * We assume that ksize callers could use whole allocated area,
	 * so we need to unpoison this area.
	 */
	kasan_unpoison_shadow(objp, size);
	return size;
}