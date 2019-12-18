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
 char* DEBUG_CACHE_DIR ; 
 int MAXPATHLEN ; 
 char* buildid_dir ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void set_buildid_dir(const char *dir)
{
	if (dir)
		scnprintf(buildid_dir, MAXPATHLEN, "%s", dir);

	/* default to $HOME/.debug */
	if (buildid_dir[0] == '\0') {
		char *home = getenv("HOME");

		if (home) {
			snprintf(buildid_dir, MAXPATHLEN, "%s/%s",
				 home, DEBUG_CACHE_DIR);
		} else {
			strncpy(buildid_dir, DEBUG_CACHE_DIR, MAXPATHLEN-1);
		}
		buildid_dir[MAXPATHLEN-1] = '\0';
	}
	/* for communicating with external commands */
	setenv("PERF_BUILDID_DIR", buildid_dir, 1);
}