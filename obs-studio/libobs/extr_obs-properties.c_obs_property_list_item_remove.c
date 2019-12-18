#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct list_data {TYPE_1__ items; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase (TYPE_1__,size_t) ; 
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_item_free (struct list_data*,scalar_t__) ; 

void obs_property_list_item_remove(obs_property_t *p, size_t idx)
{
	struct list_data *data = get_list_data(p);
	if (data && idx < data->items.num) {
		list_item_free(data, data->items.array + idx);
		da_erase(data->items, idx);
	}
}