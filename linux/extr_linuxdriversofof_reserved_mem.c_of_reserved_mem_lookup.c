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
struct reserved_mem {int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 char* kbasename (int /*<<< orphan*/ ) ; 
 struct reserved_mem* reserved_mem ; 
 int reserved_mem_count ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct reserved_mem *of_reserved_mem_lookup(struct device_node *np)
{
	const char *name;
	int i;

	if (!np->full_name)
		return NULL;

	name = kbasename(np->full_name);
	for (i = 0; i < reserved_mem_count; i++)
		if (!strcmp(reserved_mem[i].name, name))
			return &reserved_mem[i];

	return NULL;
}