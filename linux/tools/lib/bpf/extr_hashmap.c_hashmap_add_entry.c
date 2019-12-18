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
struct hashmap_entry {struct hashmap_entry* next; } ;

/* Variables and functions */

__attribute__((used)) static void hashmap_add_entry(struct hashmap_entry **pprev,
			      struct hashmap_entry *entry)
{
	entry->next = *pprev;
	*pprev = entry;
}