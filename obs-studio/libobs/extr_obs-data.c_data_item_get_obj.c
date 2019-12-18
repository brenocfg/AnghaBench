#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  TYPE_1__* (* get_obj_t ) (int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_DATA_OBJECT ; 
 scalar_t__ item_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline obs_data_t *data_item_get_obj(obs_data_item_t *item,
					    get_obj_t get_obj)
{
	obs_data_t *obj = item_valid(item, OBS_DATA_OBJECT) ? get_obj(item)
							    : NULL;

	if (obj)
		os_atomic_inc_long(&obj->ref);
	return obj;
}