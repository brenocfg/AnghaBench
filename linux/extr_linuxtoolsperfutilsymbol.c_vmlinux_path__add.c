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
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/ ** vmlinux_path ; 
 size_t vmlinux_path__nr_entries ; 

__attribute__((used)) static int vmlinux_path__add(const char *new_entry)
{
	vmlinux_path[vmlinux_path__nr_entries] = strdup(new_entry);
	if (vmlinux_path[vmlinux_path__nr_entries] == NULL)
		return -1;
	++vmlinux_path__nr_entries;

	return 0;
}