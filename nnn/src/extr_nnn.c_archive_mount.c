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
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  F_NORMAL ; 
 size_t OPERATION_FAILED ; 
 int TRUE ; 
 size_t UTIL_MISSING ; 
 int /*<<< orphan*/  cfgdir ; 
 int /*<<< orphan*/  create_dir (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getutil (char*) ; 
 int /*<<< orphan*/ * messages ; 
 int /*<<< orphan*/  mkpath (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printwait (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ spawn (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static bool archive_mount(char *name, char *path, char *newpath, int *presel)
{
	char *dir, *cmd = "archivemount";
	size_t len;

	if (!getutil(cmd)) {
		printwait(messages[UTIL_MISSING], presel);
		return FALSE;
	}

	dir = strdup(name);
	if (!dir)
		return FALSE;

	len = strlen(dir);

	while (len > 1)
		if (dir[--len] == '.') {
			dir[len] = '\0';
			break;
		}

	DPRINTF_S(dir);

	/* Create the mount point */
	mkpath(cfgdir, dir, newpath);
	free(dir);

	if (!create_dir(newpath)) {
		printwait(strerror(errno), presel);
		return FALSE;
	}

	/* Mount archive */
	DPRINTF_S(name);
	DPRINTF_S(newpath);
	if (spawn(cmd, name, newpath, path, F_NORMAL)) {
		printwait(messages[OPERATION_FAILED], presel);
		return FALSE;
	}

	return TRUE;
}