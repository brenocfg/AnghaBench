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
struct obs_data_item {size_t autoselect_size; int type; scalar_t__ default_size; void* default_len; scalar_t__ data_size; void* data_len; } ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 void* get_align_size (scalar_t__) ; 
 int /*<<< orphan*/  get_item_autoselect_data (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_autoselect_data_addref (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_autoselect_data_release (struct obs_data_item*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 struct obs_data_item* obs_data_item_ensure_capacity (struct obs_data_item*) ; 

__attribute__((used)) static inline void
obs_data_item_set_autoselect_data(struct obs_data_item **p_item,
				  const void *data, size_t size,
				  enum obs_data_type type)
{
	if (!p_item || !*p_item)
		return;

	struct obs_data_item *item = *p_item;
	item_autoselect_data_release(item);

	item->autoselect_size = size;
	item->type = type;
	item->data_len = item->data_size ? get_align_size(item->data_size) : 0;
	item->default_len =
		item->default_size ? get_align_size(item->default_size) : 0;
	item = obs_data_item_ensure_capacity(item);

	if (size) {
		memcpy(get_item_autoselect_data(item), data, size);
		item_autoselect_data_addref(item);
	}

	*p_item = item;
}