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
struct passwd {int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  pwdbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  pqGetpwuid (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
get_home_path(char *ret_path)
{
#ifndef WIN32
	char		pwdbuf[BUFSIZ];
	struct passwd pwdstr;
	struct passwd *pwd = NULL;

	(void) pqGetpwuid(geteuid(), &pwdstr, pwdbuf, sizeof(pwdbuf), &pwd);
	if (pwd == NULL)
		return false;
	strlcpy(ret_path, pwd->pw_dir, MAXPGPATH);
	return true;
#else
	char	   *tmppath;

	/*
	 * Note: We use getenv() here because the more modern SHGetFolderPath()
	 * would force the backend to link with shell32.lib, which eats valuable
	 * desktop heap.  XXX This function is used only in psql, which already
	 * brings in shell32 via libpq.  Moving this function to its own file
	 * would keep it out of the backend, freeing it from this concern.
	 */
	tmppath = getenv("APPDATA");
	if (!tmppath)
		return false;
	snprintf(ret_path, MAXPGPATH, "%s/postgresql", tmppath);
	return true;
#endif
}