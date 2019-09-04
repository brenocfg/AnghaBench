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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 void* kasan_mem_to_shadow (void const*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kasan_poison_shadow(const void *address, size_t size, u8 value)
{
	void *shadow_start, *shadow_end;

	shadow_start = kasan_mem_to_shadow(address);
	shadow_end = kasan_mem_to_shadow(address + size);

	memset(shadow_start, value, shadow_end - shadow_start);
}