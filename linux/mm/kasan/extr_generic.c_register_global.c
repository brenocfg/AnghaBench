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
struct kasan_global {scalar_t__ size_with_redzone; scalar_t__ beg; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASAN_GLOBAL_REDZONE ; 
 int /*<<< orphan*/  KASAN_SHADOW_SCALE_SIZE ; 
 int /*<<< orphan*/  kasan_poison_shadow (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void register_global(struct kasan_global *global)
{
	size_t aligned_size = round_up(global->size, KASAN_SHADOW_SCALE_SIZE);

	kasan_unpoison_shadow(global->beg, global->size);

	kasan_poison_shadow(global->beg + aligned_size,
		global->size_with_redzone - aligned_size,
		KASAN_GLOBAL_REDZONE);
}