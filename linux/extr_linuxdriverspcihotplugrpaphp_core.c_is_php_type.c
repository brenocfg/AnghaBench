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
 unsigned long simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static int is_php_type(char *drc_type)
{
	unsigned long value;
	char *endptr;

	/* PCI Hotplug nodes have an integer for drc_type */
	value = simple_strtoul(drc_type, &endptr, 10);
	if (endptr == drc_type)
		return 0;

	return 1;
}