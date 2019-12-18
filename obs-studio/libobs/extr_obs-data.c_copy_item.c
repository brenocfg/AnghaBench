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
struct obs_data_item {int /*<<< orphan*/  type; int /*<<< orphan*/  data_size; } ;
struct obs_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_DATA_ARRAY ; 
 int /*<<< orphan*/  OBS_DATA_OBJECT ; 
 int /*<<< orphan*/  copy_array (struct obs_data*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_obj (struct obs_data*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_item_data (struct obs_data_item*) ; 
 char* get_item_name (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_set_array ; 
 int /*<<< orphan*/  obs_data_set_obj ; 
 int /*<<< orphan*/  set_item (struct obs_data*,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_item(struct obs_data *data, struct obs_data_item *item)
{
	const char *name = get_item_name(item);
	void *ptr = get_item_data(item);

	if (item->type == OBS_DATA_OBJECT) {
		obs_data_t **obj = item->data_size ? ptr : NULL;

		if (obj)
			copy_obj(data, name, *obj, obs_data_set_obj);

	} else if (item->type == OBS_DATA_ARRAY) {
		obs_data_array_t **array = item->data_size ? ptr : NULL;

		if (array)
			copy_array(data, name, *array, obs_data_set_array);

	} else {
		if (item->data_size)
			set_item(data, NULL, name, ptr, item->data_size,
				 item->type);
	}
}