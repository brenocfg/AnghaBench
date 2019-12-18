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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  pathname ;
typedef  int int64 ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  DIR ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ DEFAULTTABLESPACE_OID ; 
 int /*<<< orphan*/  DEFAULT_ROLE_READ_ALL_STATS ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  GetUserId () ; 
 int MAXPGPATH ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int /*<<< orphan*/  OBJECT_TABLESPACE ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* TABLESPACE_VERSION_DIRECTORY ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ db_dir_size (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  get_tablespace_name (scalar_t__) ; 
 int /*<<< orphan*/  is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_tablespace_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int64
calculate_tablespace_size(Oid tblspcOid)
{
	char		tblspcPath[MAXPGPATH];
	char		pathname[MAXPGPATH * 2];
	int64		totalsize = 0;
	DIR		   *dirdesc;
	struct dirent *direntry;
	AclResult	aclresult;

	/*
	 * User must be a member of pg_read_all_stats or have CREATE privilege for
	 * target tablespace, either explicitly granted or implicitly because it
	 * is default for current database.
	 */
	if (tblspcOid != MyDatabaseTableSpace &&
		!is_member_of_role(GetUserId(), DEFAULT_ROLE_READ_ALL_STATS))
	{
		aclresult = pg_tablespace_aclcheck(tblspcOid, GetUserId(), ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, OBJECT_TABLESPACE,
						   get_tablespace_name(tblspcOid));
	}

	if (tblspcOid == DEFAULTTABLESPACE_OID)
		snprintf(tblspcPath, MAXPGPATH, "base");
	else if (tblspcOid == GLOBALTABLESPACE_OID)
		snprintf(tblspcPath, MAXPGPATH, "global");
	else
		snprintf(tblspcPath, MAXPGPATH, "pg_tblspc/%u/%s", tblspcOid,
				 TABLESPACE_VERSION_DIRECTORY);

	dirdesc = AllocateDir(tblspcPath);

	if (!dirdesc)
		return -1;

	while ((direntry = ReadDir(dirdesc, tblspcPath)) != NULL)
	{
		struct stat fst;

		CHECK_FOR_INTERRUPTS();

		if (strcmp(direntry->d_name, ".") == 0 ||
			strcmp(direntry->d_name, "..") == 0)
			continue;

		snprintf(pathname, sizeof(pathname), "%s/%s", tblspcPath, direntry->d_name);

		if (stat(pathname, &fst) < 0)
		{
			if (errno == ENOENT)
				continue;
			else
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not stat file \"%s\": %m", pathname)));
		}

		if (S_ISDIR(fst.st_mode))
			totalsize += db_dir_size(pathname);

		totalsize += fst.st_size;
	}

	FreeDir(dirdesc);

	return totalsize;
}