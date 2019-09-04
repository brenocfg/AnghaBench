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
struct kernel_sym {int address; } ;

/* Variables and functions */

__attribute__((used)) static int kernel_syms_cmp(const void *sym_a, const void *sym_b)
{
	return ((struct kernel_sym *)sym_a)->address -
	       ((struct kernel_sym *)sym_b)->address;
}