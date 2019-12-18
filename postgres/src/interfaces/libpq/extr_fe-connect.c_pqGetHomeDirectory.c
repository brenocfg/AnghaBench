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
typedef  int /*<<< orphan*/  tmppath ;
struct passwd {int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  pwdbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  CSIDL_APPDATA ; 
 int MAX_PATH ; 
 scalar_t__ SHGetFolderPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  pqGetpwuid (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

bool
pqGetHomeDirectory(char *buf, int bufsize)
{
#ifndef WIN32
	char		pwdbuf[BUFSIZ];
	struct passwd pwdstr;
	struct passwd *pwd = NULL;

	(void) pqGetpwuid(geteuid(), &pwdstr, pwdbuf, sizeof(pwdbuf), &pwd);
	if (pwd == NULL)
		return false;
	strlcpy(buf, pwd->pw_dir, bufsize);
	return true;
#else
	char		tmppath[MAX_PATH];

	ZeroMemory(tmppath, sizeof(tmppath));
	if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, tmppath) != S_OK)
		return false;
	snprintf(buf, bufsize, "%s/postgresql", tmppath);
	return true;
#endif
}