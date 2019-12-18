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
 int /*<<< orphan*/  SETTING_ANY_FULLSCREEN ; 
 int /*<<< orphan*/  SETTING_CAPTURE_WINDOW ; 
 int /*<<< orphan*/  SETTING_MODE ; 
 int /*<<< orphan*/  SETTING_MODE_WINDOW ; 
 int /*<<< orphan*/  SETTING_WINDOW_PRIORITY ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ using_older_non_mode_format (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mode_callback(obs_properties_t *ppts, obs_property_t *p,
			  obs_data_t *settings)
{
	bool capture_window;

	if (using_older_non_mode_format(settings)) {
		capture_window =
			!obs_data_get_bool(settings, SETTING_ANY_FULLSCREEN);
	} else {
		const char *mode = obs_data_get_string(settings, SETTING_MODE);
		capture_window = strcmp(mode, SETTING_MODE_WINDOW) == 0;
	}

	p = obs_properties_get(ppts, SETTING_CAPTURE_WINDOW);
	obs_property_set_visible(p, capture_window);

	p = obs_properties_get(ppts, SETTING_WINDOW_PRIORITY);
	obs_property_set_visible(p, capture_window);

	return true;
}