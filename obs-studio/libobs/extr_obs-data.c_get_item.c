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
struct obs_data_item {struct obs_data_item* next; } ;
struct obs_data {struct obs_data_item* first_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_item_name (struct obs_data_item*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct obs_data_item *get_item(struct obs_data *data, const char *name)
{
	if (!data)
		return NULL;

	struct obs_data_item *item = data->first_item;

	while (item) {
		if (strcmp(get_item_name(item), name) == 0)
			return item;

		item = item->next;
	}

	return NULL;
}