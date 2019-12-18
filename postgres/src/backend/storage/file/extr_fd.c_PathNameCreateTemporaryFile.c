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
struct TYPE_2__ {int /*<<< orphan*/  fdstate; } ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FD_TEMP_FILE_LIMIT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PG_BINARY ; 
 size_t PathNameOpenFile (char const*,int) ; 
 int /*<<< orphan*/  RegisterTemporaryFile (size_t) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeFiles (int /*<<< orphan*/ ) ; 
 TYPE_1__* VfdCache ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 

File
PathNameCreateTemporaryFile(const char *path, bool error_on_failure)
{
	File		file;

	ResourceOwnerEnlargeFiles(CurrentResourceOwner);

	/*
	 * Open the file.  Note: we don't use O_EXCL, in case there is an orphaned
	 * temp file that can be reused.
	 */
	file = PathNameOpenFile(path, O_RDWR | O_CREAT | O_TRUNC | PG_BINARY);
	if (file <= 0)
	{
		if (error_on_failure)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not create temporary file \"%s\": %m",
							path)));
		else
			return file;
	}

	/* Mark it for temp_file_limit accounting. */
	VfdCache[file].fdstate |= FD_TEMP_FILE_LIMIT;

	/* Register it for automatic close. */
	RegisterTemporaryFile(file);

	return file;
}