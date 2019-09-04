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
 int /*<<< orphan*/  KASAN_SHADOW_SCALE_SIZE ; 
 int /*<<< orphan*/  KASAN_USE_AFTER_SCOPE ; 
 int /*<<< orphan*/  kasan_poison_shadow (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (size_t,int /*<<< orphan*/ ) ; 

void __asan_poison_stack_memory(const void *addr, size_t size)
{
	/*
	 * Addr is KASAN_SHADOW_SCALE_SIZE-aligned and the object is surrounded
	 * by redzones, so we simply round up size to simplify logic.
	 */
	kasan_poison_shadow(addr, round_up(size, KASAN_SHADOW_SCALE_SIZE),
			    KASAN_USE_AFTER_SCOPE);
}