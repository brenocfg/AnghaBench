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
typedef  int /*<<< orphan*/  uint8_t ;
struct obs_data_item {size_t data_size; int type; size_t data_len; scalar_t__ autoselect_size; scalar_t__ default_len; scalar_t__ default_size; } ;
typedef  int ptrdiff_t ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 size_t get_align_size (size_t) ; 
 scalar_t__ get_default_data_ptr (struct obs_data_item*) ; 
 int /*<<< orphan*/  get_item_data (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_data_addref (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_data_release (struct obs_data_item*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 struct obs_data_item* obs_data_item_ensure_capacity (struct obs_data_item*) ; 

__attribute__((used)) static inline void obs_data_item_setdata(struct obs_data_item **p_item,
					 const void *data, size_t size,
					 enum obs_data_type type)
{
	if (!p_item || !*p_item)
		return;

	struct obs_data_item *item = *p_item;
	ptrdiff_t old_default_data_pos =
		(uint8_t *)get_default_data_ptr(item) - (uint8_t *)item;
	item_data_release(item);

	item->data_size = size;
	item->type = type;
	item->data_len = (item->default_size || item->autoselect_size)
				 ? get_align_size(size)
				 : size;
	item = obs_data_item_ensure_capacity(item);

	if (item->default_size || item->autoselect_size)
		memmove(get_default_data_ptr(item),
			(uint8_t *)item + old_default_data_pos,
			item->default_len + item->autoselect_size);

	if (size) {
		memcpy(get_item_data(item), data, size);
		item_data_addref(item);
	}

	*p_item = item;
}