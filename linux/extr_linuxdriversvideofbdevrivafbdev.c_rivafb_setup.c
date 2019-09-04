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
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  backlight ; 
 int flatpanel ; 
 int forceCRTC ; 
 char* mode_option ; 
 int noaccel ; 
 int nomtrr ; 
 int /*<<< orphan*/  simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strictmode ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int rivafb_setup(char *options)
{
	char *this_opt;

	NVTRACE_ENTER();
	if (!options || !*options)
		return 0;

	while ((this_opt = strsep(&options, ",")) != NULL) {
		if (!strncmp(this_opt, "forceCRTC", 9)) {
			char *p;
			
			p = this_opt + 9;
			if (!*p || !*(++p)) continue; 
			forceCRTC = *p - '0';
			if (forceCRTC < 0 || forceCRTC > 1) 
				forceCRTC = -1;
		} else if (!strncmp(this_opt, "flatpanel", 9)) {
			flatpanel = 1;
		} else if (!strncmp(this_opt, "backlight:", 10)) {
			backlight = simple_strtoul(this_opt+10, NULL, 0);
		} else if (!strncmp(this_opt, "nomtrr", 6)) {
			nomtrr = 1;
		} else if (!strncmp(this_opt, "strictmode", 10)) {
			strictmode = 1;
		} else if (!strncmp(this_opt, "noaccel", 7)) {
			noaccel = 1;
		} else
			mode_option = this_opt;
	}
	NVTRACE_LEAVE();
	return 0;
}