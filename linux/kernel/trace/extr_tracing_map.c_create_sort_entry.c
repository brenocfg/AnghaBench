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
struct tracing_map_sort_entry {struct tracing_map_elt* elt; void* key; } ;
struct tracing_map_elt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tracing_map_sort_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tracing_map_sort_entry *
create_sort_entry(void *key, struct tracing_map_elt *elt)
{
	struct tracing_map_sort_entry *sort_entry;

	sort_entry = kzalloc(sizeof(*sort_entry), GFP_KERNEL);
	if (!sort_entry)
		return NULL;

	sort_entry->key = key;
	sort_entry->elt = elt;

	return sort_entry;
}