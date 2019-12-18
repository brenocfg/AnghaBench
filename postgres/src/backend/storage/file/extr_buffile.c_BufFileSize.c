#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int numFiles; int /*<<< orphan*/  name; int /*<<< orphan*/ * files; int /*<<< orphan*/ * fileset; } ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FilePathName (int /*<<< orphan*/ ) ; 
 scalar_t__ FileSize (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_PHYSICAL_FILESIZE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int64
BufFileSize(BufFile *file)
{
	int64		lastFileSize;

	Assert(file->fileset != NULL);

	/* Get the size of the last physical file. */
	lastFileSize = FileSize(file->files[file->numFiles - 1]);
	if (lastFileSize < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not determine size of temporary file \"%s\" from BufFile \"%s\": %m",
						FilePathName(file->files[file->numFiles - 1]),
						file->name)));

	return ((file->numFiles - 1) * (int64) MAX_PHYSICAL_FILESIZE) +
		lastFileSize;
}