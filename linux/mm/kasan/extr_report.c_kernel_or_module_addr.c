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
 scalar_t__ _end ; 
 scalar_t__ _stext ; 
 scalar_t__ is_module_address (unsigned long) ; 

__attribute__((used)) static inline bool kernel_or_module_addr(const void *addr)
{
	if (addr >= (void *)_stext && addr < (void *)_end)
		return true;
	if (is_module_address((unsigned long)addr))
		return true;
	return false;
}