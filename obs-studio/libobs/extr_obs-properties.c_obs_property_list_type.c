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
struct list_data {int type; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  enum obs_combo_type { ____Placeholder_obs_combo_type } obs_combo_type ;

/* Variables and functions */
 int OBS_COMBO_TYPE_INVALID ; 
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 

enum obs_combo_type obs_property_list_type(obs_property_t *p)
{
	struct list_data *data = get_list_data(p);
	return data ? data->type : OBS_COMBO_TYPE_INVALID;
}