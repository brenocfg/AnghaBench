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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_service_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*) ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get_param (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool show_all_services_toggled(obs_properties_t *ppts, obs_property_t *p,
				      obs_data_t *settings)
{
	const char *cur_service = obs_data_get_string(settings, "service");
	bool show_all = obs_data_get_bool(settings, "show_all");

	json_t *root = obs_properties_get_param(ppts);
	if (!root)
		return false;

	build_service_list(obs_properties_get(ppts, "service"), root, show_all,
			   cur_service);

	UNUSED_PARAMETER(p);
	return true;
}