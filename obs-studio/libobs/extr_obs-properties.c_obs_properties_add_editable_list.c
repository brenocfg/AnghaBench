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
struct obs_property {int dummy; } ;
struct editable_list_data {int type; void* default_path; void* filter; } ;
typedef  struct obs_property obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  enum obs_editable_list_type { ____Placeholder_obs_editable_list_type } obs_editable_list_type ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_EDITABLE_LIST ; 
 void* bstrdup (char const*) ; 
 struct editable_list_data* get_property_data (struct obs_property*) ; 
 scalar_t__ has_prop (int /*<<< orphan*/ *,char const*) ; 
 struct obs_property* new_prop (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 

obs_property_t *
obs_properties_add_editable_list(obs_properties_t *props, const char *name,
				 const char *desc,
				 enum obs_editable_list_type type,
				 const char *filter, const char *default_path)
{
	if (!props || has_prop(props, name))
		return NULL;
	struct obs_property *p =
		new_prop(props, name, desc, OBS_PROPERTY_EDITABLE_LIST);

	struct editable_list_data *data = get_property_data(p);
	data->type = type;
	data->filter = bstrdup(filter);
	data->default_path = bstrdup(default_path);
	return p;
}