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
typedef  scalar_t__ File ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 scalar_t__ PathNameOpenFile (char const*,int) ; 
 int /*<<< orphan*/  RegisterTemporaryFile (scalar_t__) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeFiles (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 

File
PathNameOpenTemporaryFile(const char *path)
{
	File		file;

	ResourceOwnerEnlargeFiles(CurrentResourceOwner);

	/* We open the file read-only. */
	file = PathNameOpenFile(path, O_RDONLY | PG_BINARY);

	/* If no such file, then we don't raise an error. */
	if (file <= 0 && errno != ENOENT)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open temporary file \"%s\": %m",
						path)));

	if (file > 0)
	{
		/* Register it for automatic close. */
		RegisterTemporaryFile(file);
	}

	return file;
}