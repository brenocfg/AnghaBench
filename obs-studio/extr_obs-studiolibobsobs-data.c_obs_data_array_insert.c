#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  objects; } ;
typedef  TYPE_2__ obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_insert (int /*<<< orphan*/ ,size_t,TYPE_1__**) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 

void obs_data_array_insert(obs_data_array_t *array, size_t idx, obs_data_t *obj)
{
	if (!array || !obj)
		return;

	os_atomic_inc_long(&obj->ref);
	da_insert(array->objects, idx, &obj);
}