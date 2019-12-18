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
 scalar_t__ cpu_selected_set ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int max_pkg_num ; 
 int pkg_present_set ; 
 int pkg_selected_set ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

void parse_cmdline_pkg(char *s)
{
	char *startp, *endp;
	int pkg = 0;

	if (cpu_selected_set) {
		usage();
		errx(1, "--pkg | --cpu");
	}
	pkg_selected_set = 0;

	for (startp = s; startp && *startp;) {

		if (*startp == ',') {
			startp++;
			continue;
		}

		if (*startp == '-') {
			int end_pkg;

			startp++;
			end_pkg = strtol(startp, &endp, 10);
			if (startp == endp)
				continue;

			while (pkg <= end_pkg) {
				if (pkg > max_pkg_num)
					errx(1, "Requested pkg%d exceeds max pkg%d", pkg, max_pkg_num);
				pkg_selected_set |= 1 << pkg;
				pkg++;
			}
			startp = endp;
			continue;
		}

		if (strncmp(startp, "all", 3) == 0) {
			pkg_selected_set = pkg_present_set;
			return;
		}

		pkg = strtol(startp, &endp, 10);
		if (pkg > max_pkg_num)
			errx(1, "Requested pkg%d Exceeds max pkg%d", pkg, max_pkg_num);
		pkg_selected_set |= 1 << pkg;
		startp = endp;
	}
}