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
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool alsa_devices_changed(obs_properties_t *props, obs_property_t *p,
				 obs_data_t *settings)
{
	UNUSED_PARAMETER(p);
	bool visible = false;
	const char *device_id = obs_data_get_string(settings, "device_id");

	if (strcmp(device_id, "__custom__") == 0)
		visible = true;

	obs_property_t *custom_pcm = obs_properties_get(props, "custom_pcm");

	obs_property_set_visible(custom_pcm, visible);
	obs_property_modified(custom_pcm, settings);

	return true;
}