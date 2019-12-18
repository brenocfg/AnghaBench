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
struct obs_data_item {size_t capacity; int type; size_t name_len; int ref; size_t default_len; size_t default_size; size_t autoselect_size; size_t data_len; size_t data_size; } ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 struct obs_data_item* bzalloc (size_t) ; 
 int /*<<< orphan*/  get_item_data (struct obs_data_item*) ; 
 int /*<<< orphan*/  get_item_name (struct obs_data_item*) ; 
 size_t get_name_align_size (char const*) ; 
 int /*<<< orphan*/  item_data_addref (struct obs_data_item*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct obs_data_item *obs_data_item_create(const char *name,
						  const void *data, size_t size,
						  enum obs_data_type type,
						  bool default_data,
						  bool autoselect_data)
{
	struct obs_data_item *item;
	size_t name_size, total_size;

	if (!name || !data)
		return NULL;

	name_size = get_name_align_size(name);
	total_size = name_size + sizeof(struct obs_data_item) + size;

	item = bzalloc(total_size);

	item->capacity = total_size;
	item->type = type;
	item->name_len = name_size;
	item->ref = 1;

	if (default_data) {
		item->default_len = size;
		item->default_size = size;

	} else if (autoselect_data) {
		item->autoselect_size = size;

	} else {
		item->data_len = size;
		item->data_size = size;
	}

	strcpy(get_item_name(item), name);
	memcpy(get_item_data(item), data, size);

	item_data_addref(item);
	return item;
}