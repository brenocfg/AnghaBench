#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fdstate; } ;
typedef  scalar_t__ Oid ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 scalar_t__ DEFAULTTABLESPACE_OID ; 
 int FD_DELETE_AT_CLOSE ; 
 int FD_TEMP_FILE_LIMIT ; 
 scalar_t__ GetNextTempTableSpace () ; 
 scalar_t__ MyDatabaseTableSpace ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 size_t OpenTemporaryFileInTablespace (scalar_t__,int) ; 
 int /*<<< orphan*/  RegisterTemporaryFile (size_t) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeFiles (int /*<<< orphan*/ ) ; 
 TYPE_1__* VfdCache ; 
 scalar_t__ numTempTableSpaces ; 

File
OpenTemporaryFile(bool interXact)
{
	File		file = 0;

	/*
	 * Make sure the current resource owner has space for this File before we
	 * open it, if we'll be registering it below.
	 */
	if (!interXact)
		ResourceOwnerEnlargeFiles(CurrentResourceOwner);

	/*
	 * If some temp tablespace(s) have been given to us, try to use the next
	 * one.  If a given tablespace can't be found, we silently fall back to
	 * the database's default tablespace.
	 *
	 * BUT: if the temp file is slated to outlive the current transaction,
	 * force it into the database's default tablespace, so that it will not
	 * pose a threat to possible tablespace drop attempts.
	 */
	if (numTempTableSpaces > 0 && !interXact)
	{
		Oid			tblspcOid = GetNextTempTableSpace();

		if (OidIsValid(tblspcOid))
			file = OpenTemporaryFileInTablespace(tblspcOid, false);
	}

	/*
	 * If not, or if tablespace is bad, create in database's default
	 * tablespace.  MyDatabaseTableSpace should normally be set before we get
	 * here, but just in case it isn't, fall back to pg_default tablespace.
	 */
	if (file <= 0)
		file = OpenTemporaryFileInTablespace(MyDatabaseTableSpace ?
											 MyDatabaseTableSpace :
											 DEFAULTTABLESPACE_OID,
											 true);

	/* Mark it for deletion at close and temporary file size limit */
	VfdCache[file].fdstate |= FD_DELETE_AT_CLOSE | FD_TEMP_FILE_LIMIT;

	/* Register it with the current resource owner */
	if (!interXact)
		RegisterTemporaryFile(file);

	return file;
}