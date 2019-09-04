#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ autoselect_size; } ;
typedef  TYPE_1__ obs_data_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  item_autoselect_data_release (TYPE_1__*) ; 

void obs_data_item_unset_autoselect_value(obs_data_item_t *item)
{
	if (!item || !item->autoselect_size)
		return;

	item_autoselect_data_release(item);
	item->autoselect_size = 0;
}