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
struct obs_data_number {int type; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ obs_data_item_t ;
typedef  enum obs_data_number_type { ____Placeholder_obs_data_number_type } obs_data_number_type ;

/* Variables and functions */
 scalar_t__ OBS_DATA_NUMBER ; 
 int OBS_DATA_NUM_INVALID ; 
 struct obs_data_number* get_item_data (TYPE_1__*) ; 

enum obs_data_number_type obs_data_item_numtype(obs_data_item_t *item)
{
	struct obs_data_number *num;

	if (!item || item->type != OBS_DATA_NUMBER)
		return OBS_DATA_NUM_INVALID;

	num = get_item_data(item);
	return num->type;
}