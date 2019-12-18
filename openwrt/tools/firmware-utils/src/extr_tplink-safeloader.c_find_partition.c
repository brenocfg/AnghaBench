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
struct flash_partition_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct flash_partition_entry *find_partition(
		struct flash_partition_entry *entries, size_t max_entries,
		const char *name, const char *error_msg)
{
	for (size_t i = 0; i < max_entries; i++, entries++) {
		if (strcmp(entries->name, name) == 0)
			return entries;
	}

	error(1, 0, "%s", error_msg);
	return NULL;
}