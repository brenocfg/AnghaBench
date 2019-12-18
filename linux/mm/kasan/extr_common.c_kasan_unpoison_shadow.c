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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_KASAN_SW_TAGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t KASAN_SHADOW_MASK ; 
 size_t get_tag (void const*) ; 
 scalar_t__ kasan_mem_to_shadow (void const*) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void const*,size_t,size_t) ; 
 void* reset_tag (void const*) ; 

void kasan_unpoison_shadow(const void *address, size_t size)
{
	u8 tag = get_tag(address);

	/*
	 * Perform shadow offset calculation based on untagged address, as
	 * some of the callers (e.g. kasan_unpoison_object_data) pass tagged
	 * addresses to this function.
	 */
	address = reset_tag(address);

	kasan_poison_shadow(address, size, tag);

	if (size & KASAN_SHADOW_MASK) {
		u8 *shadow = (u8 *)kasan_mem_to_shadow(address + size);

		if (IS_ENABLED(CONFIG_KASAN_SW_TAGS))
			*shadow = tag;
		else
			*shadow = size & KASAN_SHADOW_MASK;
	}
}