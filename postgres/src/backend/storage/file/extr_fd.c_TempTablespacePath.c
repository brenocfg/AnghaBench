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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ DEFAULTTABLESPACE_OID ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 char* PG_TEMP_FILES_DIR ; 
 char* TABLESPACE_VERSION_DIRECTORY ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

void
TempTablespacePath(char *path, Oid tablespace)
{
	/*
	 * Identify the tempfile directory for this tablespace.
	 *
	 * If someone tries to specify pg_global, use pg_default instead.
	 */
	if (tablespace == InvalidOid ||
		tablespace == DEFAULTTABLESPACE_OID ||
		tablespace == GLOBALTABLESPACE_OID)
		snprintf(path, MAXPGPATH, "base/%s", PG_TEMP_FILES_DIR);
	else
	{
		/* All other tablespaces are accessed via symlinks */
		snprintf(path, MAXPGPATH, "pg_tblspc/%u/%s/%s",
				 tablespace, TABLESPACE_VERSION_DIRECTORY,
				 PG_TEMP_FILES_DIR);
	}
}