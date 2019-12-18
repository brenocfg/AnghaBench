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
struct darray {size_t num; } ;
struct config_section {struct darray const items; int /*<<< orphan*/  name; } ;
typedef  struct config_item {int /*<<< orphan*/  name; } const config_item ;

/* Variables and functions */
 scalar_t__ astrcmpi (int /*<<< orphan*/ ,char const*) ; 
 void* darray_item (int,struct darray const*,size_t) ; 

__attribute__((used)) static const struct config_item *config_find_item(const struct darray *sections,
						  const char *section,
						  const char *name)
{
	size_t i, j;

	for (i = 0; i < sections->num; i++) {
		const struct config_section *sec =
			darray_item(sizeof(struct config_section), sections, i);

		if (astrcmpi(sec->name, section) == 0) {
			for (j = 0; j < sec->items.num; j++) {
				struct config_item *item =
					darray_item(sizeof(struct config_item),
						    &sec->items, j);

				if (astrcmpi(item->name, name) == 0)
					return item;
			}
		}
	}

	return NULL;
}