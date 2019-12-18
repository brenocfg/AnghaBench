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
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  printk (char*,int,char,void*) ; 

void stack_trace_print(const unsigned long *entries, unsigned int nr_entries,
		       int spaces)
{
	unsigned int i;

	if (WARN_ON(!entries))
		return;

	for (i = 0; i < nr_entries; i++)
		printk("%*c%pS\n", 1 + spaces, ' ', (void *)entries[i]);
}