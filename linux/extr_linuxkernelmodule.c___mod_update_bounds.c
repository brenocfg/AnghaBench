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
 unsigned long module_addr_max ; 
 unsigned long module_addr_min ; 

__attribute__((used)) static void __mod_update_bounds(void *base, unsigned int size)
{
	unsigned long min = (unsigned long)base;
	unsigned long max = min + size;

	if (min < module_addr_min)
		module_addr_min = min;
	if (max > module_addr_max)
		module_addr_max = max;
}