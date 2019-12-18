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
typedef  int /*<<< orphan*/  uchar ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  F_MULTI ; 
 int /*<<< orphan*/  F_NORMAL ; 
 size_t OPERATION_FAILED ; 
 int TRUE ; 
 size_t UTIL_MISSING ; 
 int /*<<< orphan*/  cfgdir ; 
 int /*<<< orphan*/  create_dir (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getutil (char*) ; 
 int /*<<< orphan*/ * messages ; 
 int /*<<< orphan*/  mkpath (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printwait (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ spawn (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* xreadline (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool sshfs_mount(char *newpath, int *presel)
{
	uchar flag = F_NORMAL;
	int r;
	char *tmp, *env, *cmd = "sshfs";

	if (!getutil(cmd)) {
		printwait(messages[UTIL_MISSING], presel);
		return FALSE;
	}

	tmp = xreadline(NULL, "host: ");
	if (!tmp[0])
		return FALSE;

	/* Create the mount point */
	mkpath(cfgdir, tmp, newpath);
	if (!create_dir(newpath)) {
		printwait(strerror(errno), presel);
		return FALSE;
	}

	/* Convert "Host" to "Host:" */
	r = strlen(tmp);
	tmp[r] = ':';
	tmp[r + 1] = '\0';

	env = getenv("NNN_SSHFS_OPTS");
	if (env)
		flag |= F_MULTI;
	else
		env = cmd;

	/* Connect to remote */
	if (spawn(env, tmp, newpath, NULL, flag)) {
		printwait(messages[OPERATION_FAILED], presel);
		return FALSE;
	}

	return TRUE;
}