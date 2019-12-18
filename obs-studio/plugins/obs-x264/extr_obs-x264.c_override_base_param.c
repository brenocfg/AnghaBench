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
struct obs_x264 {int dummy; } ;

/* Variables and functions */
 scalar_t__ astrcmpi (char*,char*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bstrdup (char const*) ; 
 scalar_t__ getparam (char const*,char**,char const**) ; 
 char* validate (struct obs_x264*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x264_preset_names ; 
 int /*<<< orphan*/  x264_profile_names ; 
 int /*<<< orphan*/  x264_tune_names ; 

__attribute__((used)) static void override_base_param(struct obs_x264 *obsx264, const char *param,
				char **preset, char **profile, char **tune)
{
	char *name;
	const char *val;

	if (getparam(param, &name, &val)) {
		if (astrcmpi(name, "preset") == 0) {
			const char *valid_name = validate(
				obsx264, val, "preset", x264_preset_names);
			if (valid_name) {
				bfree(*preset);
				*preset = bstrdup(val);
			}

		} else if (astrcmpi(name, "profile") == 0) {
			const char *valid_name = validate(
				obsx264, val, "profile", x264_profile_names);
			if (valid_name) {
				bfree(*profile);
				*profile = bstrdup(val);
			}

		} else if (astrcmpi(name, "tune") == 0) {
			const char *valid_name =
				validate(obsx264, val, "tune", x264_tune_names);
			if (valid_name) {
				bfree(*tune);
				*tune = bstrdup(val);
			}
		}

		bfree(name);
	}
}