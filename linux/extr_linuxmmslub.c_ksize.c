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
 size_t __ksize (void const*) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 

size_t ksize(const void *object)
{
	size_t size = __ksize(object);
	/* We assume that ksize callers could use whole allocated area,
	 * so we need to unpoison this area.
	 */
	kasan_unpoison_shadow(object, size);
	return size;
}