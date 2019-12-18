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
struct obs_data_item {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 scalar_t__ OBS_DATA_ARRAY ; 
 scalar_t__ OBS_DATA_OBJECT ; 
 int /*<<< orphan*/ * get_item_array (struct obs_data_item*) ; 
 int /*<<< orphan*/ * get_item_obj (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_array_addref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void item_data_addref(struct obs_data_item *item)
{
	if (item->type == OBS_DATA_OBJECT) {
		obs_data_t *obj = get_item_obj(item);
		obs_data_addref(obj);

	} else if (item->type == OBS_DATA_ARRAY) {
		obs_data_array_t *array = get_item_array(item);
		obs_data_array_addref(array);
	}
}