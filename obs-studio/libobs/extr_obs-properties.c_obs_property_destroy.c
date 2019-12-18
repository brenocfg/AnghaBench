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
struct obs_property {scalar_t__ type; struct obs_property* long_desc; struct obs_property* desc; struct obs_property* name; } ;

/* Variables and functions */
 scalar_t__ OBS_PROPERTY_EDITABLE_LIST ; 
 scalar_t__ OBS_PROPERTY_FLOAT ; 
 scalar_t__ OBS_PROPERTY_FRAME_RATE ; 
 scalar_t__ OBS_PROPERTY_GROUP ; 
 scalar_t__ OBS_PROPERTY_INT ; 
 scalar_t__ OBS_PROPERTY_LIST ; 
 scalar_t__ OBS_PROPERTY_PATH ; 
 int /*<<< orphan*/  bfree (struct obs_property*) ; 
 int /*<<< orphan*/  editable_list_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_rate_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_property_data (struct obs_property*) ; 
 int /*<<< orphan*/  group_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_data_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_property_destroy(struct obs_property *property)
{
	if (property->type == OBS_PROPERTY_LIST)
		list_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_PATH)
		path_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_EDITABLE_LIST)
		editable_list_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_FRAME_RATE)
		frame_rate_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_GROUP)
		group_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_INT)
		int_data_free(get_property_data(property));
	else if (property->type == OBS_PROPERTY_FLOAT)
		float_data_free(get_property_data(property));

	bfree(property->name);
	bfree(property->desc);
	bfree(property->long_desc);
	bfree(property);
}