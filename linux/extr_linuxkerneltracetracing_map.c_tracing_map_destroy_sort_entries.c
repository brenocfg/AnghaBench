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
struct tracing_map_sort_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_sort_entry (struct tracing_map_sort_entry*) ; 
 int /*<<< orphan*/  vfree (struct tracing_map_sort_entry**) ; 

void tracing_map_destroy_sort_entries(struct tracing_map_sort_entry **entries,
				      unsigned int n_entries)
{
	unsigned int i;

	for (i = 0; i < n_entries; i++)
		destroy_sort_entry(entries[i]);

	vfree(entries);
}