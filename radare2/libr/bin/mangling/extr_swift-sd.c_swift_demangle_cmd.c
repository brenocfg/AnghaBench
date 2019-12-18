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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int have_swift_demangle ; 
 char* r_file_path (char*) ; 
 char* r_str_newf (char*,char*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* r_sys_cmd_strf (char*,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static char *swift_demangle_cmd(const char *s) {
	/* XXX: command injection issue here */
	static char *swift_demangle = NULL;
	if (have_swift_demangle == -1) {
		if (!swift_demangle) {
			have_swift_demangle = 0;
			swift_demangle = r_file_path ("swift-demangle");
			if (!swift_demangle || !strcmp (swift_demangle, "swift-demangle")) {
				char *xcrun = r_file_path ("xcrun");
				if (xcrun) {
					if (strcmp (xcrun, "xcrun")) {
						free (swift_demangle);
						swift_demangle = r_str_newf ("%s swift-demangle", xcrun);
						have_swift_demangle = 1;
					}
					free (xcrun);
				}
			}
		}
	}
	if (swift_demangle) {
		if (strstr (s, "'") || strstr (s, "\\")) {
			/* nice try */
			return NULL;
		}
		//char *res = r_sys_cmd_strf ("%s -compact -simplified '%s'",
		char *res = r_sys_cmd_strf ("%s -compact '%s'",
			swift_demangle, s);
		if (res && !*res) {
			free (res);
			res = NULL;
		}
		r_str_trim (res);
		return res;
	}
	return NULL;
}