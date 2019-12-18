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
 int /*<<< orphan*/  fill_servers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * find_service (int /*<<< orphan*/ *,char const*,char const**) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get_param (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_list_insert_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  obs_property_list_item_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool service_selected(obs_properties_t *props, obs_property_t *p,
			     obs_data_t *settings)
{
	const char *name = obs_data_get_string(settings, "service");
	json_t *root = obs_properties_get_param(props);
	json_t *service;
	const char *new_name;

	if (!name || !*name)
		return false;

	service = find_service(root, name, &new_name);
	if (!service) {
		const char *server = obs_data_get_string(settings, "server");

		obs_property_list_insert_string(p, 0, name, name);
		obs_property_list_item_disable(p, 0, true);

		p = obs_properties_get(props, "server");
		obs_property_list_insert_string(p, 0, server, server);
		obs_property_list_item_disable(p, 0, true);
		return true;
	}
	if (new_name) {
		name = new_name;
		obs_data_set_string(settings, "service", name);
	}

	fill_servers(obs_properties_get(props, "server"), service, name);

	return true;
}