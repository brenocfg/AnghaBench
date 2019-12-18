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
struct flash_partition_entry {unsigned long base; unsigned long size; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int add_flash_partition(
		struct flash_partition_entry *part_list,
		size_t max_entries,
		const char *name,
		unsigned long base,
		unsigned long size)
{
	size_t ptr;
	/* check if the list has a free entry */
	for (ptr = 0; ptr < max_entries; ptr++, part_list++) {
		if (part_list->name == NULL &&
				part_list->base == 0 &&
				part_list->size == 0)
			break;
	}

	if (ptr == max_entries) {
		error(1, 0, "No free flash part entry available.");
	}

	part_list->name = calloc(1, strlen(name) + 1);
	if (!part_list->name) {
		error(1, 0, "Unable to allocate memory");
	}

	memcpy((char *)part_list->name, name, strlen(name));
	part_list->base = base;
	part_list->size = size;

	return 0;
}