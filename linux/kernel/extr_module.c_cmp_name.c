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
 int /*<<< orphan*/  kernel_symbol_name (void const*) ; 
 int strcmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_name(const void *name, const void *sym)
{
	return strcmp(name, kernel_symbol_name(sym));
}