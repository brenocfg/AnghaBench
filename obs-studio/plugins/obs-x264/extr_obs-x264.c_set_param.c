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
struct obs_x264 {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 char* OPENCL_ALIAS ; 
 int /*<<< orphan*/  bfree (char*) ; 
 scalar_t__ getparam (char const*,char**,char const**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 scalar_t__ x264_param_parse (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static inline void set_param(struct obs_x264 *obsx264, const char *param)
{
	char *name;
	const char *val;

	if (getparam(param, &name, &val)) {
		if (strcmp(name, "preset") != 0 &&
		    strcmp(name, "profile") != 0 && strcmp(name, "tune") != 0 &&
		    strcmp(name, "fps") != 0 &&
		    strcmp(name, "force-cfr") != 0 &&
		    strcmp(name, "width") != 0 && strcmp(name, "height") != 0 &&
		    strcmp(name, "opencl") != 0) {
			if (strcmp(name, OPENCL_ALIAS) == 0)
				strcpy(name, "opencl");
			if (x264_param_parse(&obsx264->params, name, val) != 0)
				warn("x264 param: %s failed", param);
		}

		bfree(name);
	}
}