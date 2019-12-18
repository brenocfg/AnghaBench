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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_COLOR_TYPE ; 
 int /*<<< orphan*/  SETTING_KEY_COLOR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool key_type_changed(obs_properties_t *props, obs_property_t *p,
			     obs_data_t *settings)
{
	const char *type = obs_data_get_string(settings, SETTING_COLOR_TYPE);
	bool custom = strcmp(type, "custom") == 0;

	obs_property_set_visible(obs_properties_get(props, SETTING_KEY_COLOR),
				 custom);

	UNUSED_PARAMETER(p);
	return true;
}