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
struct obs_output_info {int /*<<< orphan*/ * (* get_properties ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 struct obs_output_info* find_output (char const*) ; 
 int /*<<< orphan*/ * get_defaults (struct obs_output_info const*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_properties_apply_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 

obs_properties_t *obs_get_output_properties(const char *id)
{
	const struct obs_output_info *info = find_output(id);
	if (info && info->get_properties) {
		obs_data_t *defaults = get_defaults(info);
		obs_properties_t *properties;

		properties = info->get_properties(NULL);
		obs_properties_apply_settings(properties, defaults);
		obs_data_release(defaults);
		return properties;
	}
	return NULL;
}