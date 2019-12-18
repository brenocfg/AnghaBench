#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_data_item {int dummy; } ;
struct obs_data {TYPE_1__* first_item; } ;
struct TYPE_7__ {struct TYPE_7__* next; struct obs_data* parent; } ;
typedef  TYPE_1__ obs_data_item_t ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 int /*<<< orphan*/  get_item_name (TYPE_1__*) ; 
 TYPE_1__* obs_data_first (struct obs_data*) ; 
 TYPE_1__* obs_data_item_create (char const*,void const*,size_t,int,int,int) ; 
 int /*<<< orphan*/  obs_data_item_next (TYPE_1__**) ; 
 int /*<<< orphan*/  obs_data_item_release (TYPE_1__**) ; 
 int /*<<< orphan*/  obs_data_item_set_autoselect_data (struct obs_data_item**,void const*,size_t,int) ; 
 int /*<<< orphan*/  obs_data_item_set_default_data (struct obs_data_item**,void const*,size_t,int) ; 
 int /*<<< orphan*/  obs_data_item_setdata (struct obs_data_item**,void const*,size_t,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void set_item_data(struct obs_data *data, struct obs_data_item **item,
			  const char *name, const void *ptr, size_t size,
			  enum obs_data_type type, bool default_data,
			  bool autoselect_data)
{
	obs_data_item_t *new_item = NULL;

	if ((!item || (item && !*item)) && data) {
		new_item = obs_data_item_create(name, ptr, size, type,
						default_data, autoselect_data);

		obs_data_item_t *prev = obs_data_first(data);
		obs_data_item_t *next = obs_data_first(data);
		obs_data_item_next(&next);
		for (; prev && next;
		     obs_data_item_next(&prev), obs_data_item_next(&next)) {
			if (strcmp(get_item_name(next), name) > 0)
				break;
		}

		new_item->parent = data;
		if (prev && strcmp(get_item_name(prev), name) < 0) {
			prev->next = new_item;
			new_item->next = next;

		} else {
			data->first_item = new_item;
			new_item->next = prev;
		}

		if (!prev)
			data->first_item = new_item;

		obs_data_item_release(&prev);
		obs_data_item_release(&next);

	} else if (default_data) {
		obs_data_item_set_default_data(item, ptr, size, type);
	} else if (autoselect_data) {
		obs_data_item_set_autoselect_data(item, ptr, size, type);
	} else {
		obs_data_item_setdata(item, ptr, size, type);
	}
}