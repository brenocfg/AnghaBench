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
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 int OBS_DATA_ARRAY ; 
 int OBS_DATA_BOOLEAN ; 
 int OBS_DATA_NUMBER ; 
 int OBS_DATA_OBJECT ; 
 int OBS_DATA_STRING ; 
 char* get_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/ * obs_data_first (int /*<<< orphan*/ *) ; 
 int obs_data_item_gettype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_item_has_user_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_item_next (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_json_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_json_bool (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_json_number (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_json_obj (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_json_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *obs_data_to_json(obs_data_t *data)
{
	json_t *json = json_object();
	obs_data_item_t *item = NULL;

	for (item = obs_data_first(data); item; obs_data_item_next(&item)) {
		enum obs_data_type type = obs_data_item_gettype(item);
		const char *name = get_item_name(item);

		if (!obs_data_item_has_user_value(item))
			continue;

		if (type == OBS_DATA_STRING)
			set_json_string(json, name, item);
		else if (type == OBS_DATA_NUMBER)
			set_json_number(json, name, item);
		else if (type == OBS_DATA_BOOLEAN)
			set_json_bool(json, name, item);
		else if (type == OBS_DATA_OBJECT)
			set_json_obj(json, name, item);
		else if (type == OBS_DATA_ARRAY)
			set_json_array(json, name, item);
	}

	return json;
}