#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; TYPE_1__* array; } ;
struct list_data {TYPE_2__ items; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
struct TYPE_3__ {int disabled; } ;

/* Variables and functions */
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 

void obs_property_list_item_disable(obs_property_t *p, size_t idx,
				    bool disabled)
{
	struct list_data *data = get_list_data(p);
	if (!data || idx >= data->items.num)
		return;
	data->items.array[idx].disabled = disabled;
}