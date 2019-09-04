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
struct kernel_symbol {unsigned long value; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long kernel_symbol_value(const struct kernel_symbol *sym)
{
#ifdef CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	return (unsigned long)offset_to_ptr(&sym->value_offset);
#else
	return sym->value;
#endif
}