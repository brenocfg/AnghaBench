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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ HMODULE ;

/* Variables and functions */

__attribute__((used)) static inline void *get_offset_addr(HMODULE module, uint32_t offset)
{
	return (void*)((uintptr_t)module + (uintptr_t)offset);
}