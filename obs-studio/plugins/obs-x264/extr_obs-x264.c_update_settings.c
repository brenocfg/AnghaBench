#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int b_repeat_headers; } ;
struct obs_x264 {TYPE_1__ params; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  apply_x264_profile (struct obs_x264*,char*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 char* bstrdup (char*) ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  override_base_params (struct obs_x264*,char**,char**,char**,char**) ; 
 int reset_x264_params (struct obs_x264*,char*,char*) ; 
 int /*<<< orphan*/  strlist_free (char**) ; 
 char** strlist_split (char const*,char,int) ; 
 int /*<<< orphan*/  update_params (struct obs_x264*,int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static bool update_settings(struct obs_x264 *obsx264, obs_data_t *settings,
			    bool update)
{
	char *preset = bstrdup(obs_data_get_string(settings, "preset"));
	char *profile = bstrdup(obs_data_get_string(settings, "profile"));
	char *tune = bstrdup(obs_data_get_string(settings, "tune"));
	const char *opts = obs_data_get_string(settings, "x264opts");

	char **paramlist;
	bool success = true;

	paramlist = strlist_split(opts, ' ', false);

	if (!update)
		blog(LOG_INFO, "---------------------------------");

	if (!obsx264->context) {
		override_base_params(obsx264, paramlist, &preset, &profile,
				     &tune);

		if (preset && *preset)
			info("preset: %s", preset);
		if (profile && *profile)
			info("profile: %s", profile);
		if (tune && *tune)
			info("tune: %s", tune);

		success = reset_x264_params(obsx264, preset, tune);
	}

	if (success) {
		update_params(obsx264, settings, paramlist, update);
		if (opts && *opts && !update)
			info("custom settings: %s", opts);

		if (!obsx264->context)
			apply_x264_profile(obsx264, profile);
	}

	obsx264->params.b_repeat_headers = false;

	strlist_free(paramlist);
	bfree(preset);
	bfree(profile);
	bfree(tune);

	return success;
}