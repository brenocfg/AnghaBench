#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ obs_data_t ;
struct TYPE_6__ {size_t num; TYPE_2__** array; } ;
struct TYPE_8__ {TYPE_1__ objects; } ;
typedef  TYPE_3__ obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 

obs_data_t *obs_data_array_item(obs_data_array_t *array, size_t idx)
{
	obs_data_t *data;

	if (!array)
		return NULL;

	data = (idx < array->objects.num) ? array->objects.array[idx] : NULL;

	if (data)
		os_atomic_inc_long(&data->ref);
	return data;
}