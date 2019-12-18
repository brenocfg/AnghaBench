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
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 size_t obs_data_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_array_item (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_item_get_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_to_json (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_json_array(json_t *json, const char *name,
				  obs_data_item_t *item)
{
	json_t *jarray = json_array();
	obs_data_array_t *array = obs_data_item_get_array(item);
	size_t count = obs_data_array_count(array);

	for (size_t idx = 0; idx < count; idx++) {
		obs_data_t *sub_item = obs_data_array_item(array, idx);
		json_t *jitem = obs_data_to_json(sub_item);
		json_array_append_new(jarray, jitem);
		obs_data_release(sub_item);
	}

	json_object_set_new(json, name, jarray);
	obs_data_array_release(array);
}