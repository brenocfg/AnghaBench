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
struct editable_list_data {int type; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  enum obs_editable_list_type { ____Placeholder_obs_editable_list_type } obs_editable_list_type ;

/* Variables and functions */
 int OBS_EDITABLE_LIST_TYPE_STRINGS ; 
 int /*<<< orphan*/  OBS_PROPERTY_EDITABLE_LIST ; 
 struct editable_list_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum obs_editable_list_type obs_property_editable_list_type(obs_property_t *p)
{
	struct editable_list_data *data =
		get_type_data(p, OBS_PROPERTY_EDITABLE_LIST);
	return data ? data->type : OBS_EDITABLE_LIST_TYPE_STRINGS;
}