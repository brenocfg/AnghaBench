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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ HMODULE ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t vtable_offset(HMODULE module, void *cls,
		unsigned int offset)
{
	uintptr_t *vtable = *(uintptr_t**)cls;
	return (uint32_t)(vtable[offset] - (uintptr_t)module);
}