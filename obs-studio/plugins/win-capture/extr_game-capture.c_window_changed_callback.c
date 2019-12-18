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
 int /*<<< orphan*/  SETTING_CAPTURE_WINDOW ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_preserved_val (int /*<<< orphan*/ *,char const*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_property_list_item_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool window_changed_callback(obs_properties_t *ppts, obs_property_t *p,
				    obs_data_t *settings)
{
	const char *cur_val;
	bool match = false;
	size_t i = 0;

	cur_val = obs_data_get_string(settings, SETTING_CAPTURE_WINDOW);
	if (!cur_val) {
		return false;
	}

	for (;;) {
		const char *val = obs_property_list_item_string(p, i++);
		if (!val)
			break;

		if (strcmp(val, cur_val) == 0) {
			match = true;
			break;
		}
	}

	if (cur_val && *cur_val && !match) {
		insert_preserved_val(p, cur_val);
		return true;
	}

	UNUSED_PARAMETER(ppts);
	return false;
}