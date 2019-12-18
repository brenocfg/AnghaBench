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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  initfilename ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 char* RELCACHE_INIT_FILENAME ; 
 struct dirent* ReadDirExtended (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 
 int /*<<< orphan*/  unlink_initfile (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationCacheInitFileRemoveInDir(const char *tblspcpath)
{
	DIR		   *dir;
	struct dirent *de;
	char		initfilename[MAXPGPATH * 2];

	/* Scan the tablespace directory to find per-database directories */
	dir = AllocateDir(tblspcpath);

	while ((de = ReadDirExtended(dir, tblspcpath, LOG)) != NULL)
	{
		if (strspn(de->d_name, "0123456789") == strlen(de->d_name))
		{
			/* Try to remove the init file in each database */
			snprintf(initfilename, sizeof(initfilename), "%s/%s/%s",
					 tblspcpath, de->d_name, RELCACHE_INIT_FILENAME);
			unlink_initfile(initfilename, LOG);
		}
	}

	FreeDir(dir);
}