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
struct tracing_map_sort_entry {int /*<<< orphan*/  elt; scalar_t__ elt_copied; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tracing_map_sort_entry*) ; 
 int /*<<< orphan*/  tracing_map_elt_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_sort_entry(struct tracing_map_sort_entry *entry)
{
	if (!entry)
		return;

	if (entry->elt_copied)
		tracing_map_elt_free(entry->elt);

	kfree(entry);
}