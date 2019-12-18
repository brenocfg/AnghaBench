#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; struct config_item* array; } ;
struct config_section {int /*<<< orphan*/  name; TYPE_1__ items; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_item_free (struct config_item*) ; 
 int /*<<< orphan*/  darray_free (TYPE_1__*) ; 

__attribute__((used)) static inline void config_section_free(struct config_section *section)
{
	struct config_item *items = section->items.array;
	size_t i;

	for (i = 0; i < section->items.num; i++)
		config_item_free(items + i);

	darray_free(&section->items);
	bfree(section->name);
}