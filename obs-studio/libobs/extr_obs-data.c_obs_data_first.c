#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* first_item; } ;
typedef  TYPE_1__ obs_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ obs_data_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 

obs_data_item_t *obs_data_first(obs_data_t *data)
{
	if (!data)
		return NULL;

	if (data->first_item)
		os_atomic_inc_long(&data->first_item->ref);
	return data->first_item;
}