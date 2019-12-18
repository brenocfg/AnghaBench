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

/* Variables and functions */
 int /*<<< orphan*/  OBS_TEXT_DEFAULT ; 
 int /*<<< orphan*/  OBS_TEXT_PASSWORD ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obs_properties_add_text (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_auth_modified ; 

__attribute__((used)) static obs_properties_t *rtmp_custom_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *ppts = obs_properties_create();
	obs_property_t *p;

	obs_properties_add_text(ppts, "server", "URL", OBS_TEXT_DEFAULT);

	obs_properties_add_text(ppts, "key", obs_module_text("StreamKey"),
				OBS_TEXT_PASSWORD);

	p = obs_properties_add_bool(ppts, "use_auth",
				    obs_module_text("UseAuth"));
	obs_properties_add_text(ppts, "username", obs_module_text("Username"),
				OBS_TEXT_DEFAULT);
	obs_properties_add_text(ppts, "password", obs_module_text("Password"),
				OBS_TEXT_PASSWORD);
	obs_property_set_modified_callback(p, use_auth_modified);
	return ppts;
}