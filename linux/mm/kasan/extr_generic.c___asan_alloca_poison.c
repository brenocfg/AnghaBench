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
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  KASAN_ALLOCA_LEFT ; 
 scalar_t__ KASAN_ALLOCA_REDZONE_SIZE ; 
 int /*<<< orphan*/  KASAN_ALLOCA_RIGHT ; 
 scalar_t__ KASAN_SHADOW_SCALE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 
 size_t round_down (size_t,scalar_t__) ; 
 size_t round_up (size_t,scalar_t__) ; 

void __asan_alloca_poison(unsigned long addr, size_t size)
{
	size_t rounded_up_size = round_up(size, KASAN_SHADOW_SCALE_SIZE);
	size_t padding_size = round_up(size, KASAN_ALLOCA_REDZONE_SIZE) -
			rounded_up_size;
	size_t rounded_down_size = round_down(size, KASAN_SHADOW_SCALE_SIZE);

	const void *left_redzone = (const void *)(addr -
			KASAN_ALLOCA_REDZONE_SIZE);
	const void *right_redzone = (const void *)(addr + rounded_up_size);

	WARN_ON(!IS_ALIGNED(addr, KASAN_ALLOCA_REDZONE_SIZE));

	kasan_unpoison_shadow((const void *)(addr + rounded_down_size),
			      size - rounded_down_size);
	kasan_poison_shadow(left_redzone, KASAN_ALLOCA_REDZONE_SIZE,
			KASAN_ALLOCA_LEFT);
	kasan_poison_shadow(right_redzone,
			padding_size + KASAN_ALLOCA_REDZONE_SIZE,
			KASAN_ALLOCA_RIGHT);
}