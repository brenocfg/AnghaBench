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
struct syscall_metadata {char const* name; } ;

/* Variables and functions */
 struct syscall_metadata* syscall_nr_to_meta (int) ; 

const char *get_syscall_name(int syscall)
{
	struct syscall_metadata *entry;

	entry = syscall_nr_to_meta(syscall);
	if (!entry)
		return NULL;

	return entry->name;
}