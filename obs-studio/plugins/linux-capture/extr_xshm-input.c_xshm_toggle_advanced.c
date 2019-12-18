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
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static bool xshm_toggle_advanced(obs_properties_t *props, obs_property_t *p,
				 obs_data_t *settings)
{
	UNUSED_PARAMETER(p);
	const bool visible = obs_data_get_bool(settings, "advanced");
	obs_property_t *server = obs_properties_get(props, "server");

	obs_property_set_visible(server, visible);

	/* trigger server changed callback so the screen list is refreshed */
	obs_property_modified(server, settings);

	return true;
}