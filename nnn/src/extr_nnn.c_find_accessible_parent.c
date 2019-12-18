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
 scalar_t__ NAME_MAX ; 
 scalar_t__ PATH_MAX ; 
 char* dirname (char*) ; 
 scalar_t__ istopdir (char*) ; 
 int /*<<< orphan*/  printmsg (char*) ; 
 char* visit_parent (char*,char*,int*) ; 
 char* xbasename (char*) ; 
 int /*<<< orphan*/  xdelay () ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static void find_accessible_parent(char *path, char *newpath, char *lastname, int *presel)
{
	char *dir;

	/* Save history */
	xstrlcpy(lastname, xbasename(path), NAME_MAX + 1);

	xstrlcpy(newpath, path, PATH_MAX);
	while (true) {
		dir = visit_parent(path, newpath, presel);
		if (istopdir(path) || istopdir(newpath)) {
			if (!dir)
				dir = dirname(newpath);
			break;
		}
		if (!dir) {
			xstrlcpy(path, newpath, PATH_MAX);
			continue;
		}
		break;
	}

	xstrlcpy(path, dir, PATH_MAX);

	printmsg("cannot access dir");
	xdelay();
}