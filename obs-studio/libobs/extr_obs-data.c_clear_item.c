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
struct obs_data_item {int data_len; scalar_t__ type; size_t default_len; size_t autoselect_size; scalar_t__ data_size; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 scalar_t__ OBS_DATA_ARRAY ; 
 scalar_t__ OBS_DATA_OBJECT ; 
 void* get_item_data (struct obs_data_item*) ; 
 int /*<<< orphan*/  memmove (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_item(struct obs_data_item *item)
{
	void *ptr = get_item_data(item);
	size_t size;

	if (item->data_len) {
		if (item->type == OBS_DATA_OBJECT) {
			obs_data_t **obj = item->data_size ? ptr : NULL;

			if (obj && *obj)
				obs_data_release(*obj);

		} else if (item->type == OBS_DATA_ARRAY) {
			obs_data_array_t **array = item->data_size ? ptr : NULL;

			if (array && *array)
				obs_data_array_release(*array);
		}

		size = item->default_len + item->autoselect_size;
		if (size)
			memmove(ptr, (uint8_t *)ptr + item->data_len, size);

		item->data_size = 0;
		item->data_len = 0;
	}
}