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
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 

void __asan_unpoison_stack_memory(const void *addr, size_t size)
{
	kasan_unpoison_shadow(addr, size);
}