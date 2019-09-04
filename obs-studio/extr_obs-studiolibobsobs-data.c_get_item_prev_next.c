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

__attribute__((used)) static struct obs_data_item **get_item_prev_next(struct obs_data *data,
		struct obs_data_item *current)
{
	if (!current || !data)
		return NULL;

	struct obs_data_item **prev_next = &data->first_item;
	struct obs_data_item *item       = data->first_item;

	while (item) {
		if (item == current)
			return prev_next;

		prev_next = &item->next;
		item      = item->next;
	}

	return NULL;
}