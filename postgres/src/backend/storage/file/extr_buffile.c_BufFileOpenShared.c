#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* files; int readOnly; int /*<<< orphan*/  name; int /*<<< orphan*/ * fileset; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  SharedFileSet ;
typedef  scalar_t__ File ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXPGPATH ; 
 scalar_t__ SharedFileSetOpen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SharedSegmentName (char*,char const*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,char const*) ; 
 TYPE_1__* makeBufFileCommon (int) ; 
 scalar_t__* palloc (int) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 scalar_t__* repalloc (scalar_t__*,int) ; 

BufFile *
BufFileOpenShared(SharedFileSet *fileset, const char *name)
{
	BufFile    *file;
	char		segment_name[MAXPGPATH];
	Size		capacity = 16;
	File	   *files;
	int			nfiles = 0;

	files = palloc(sizeof(File) * capacity);

	/*
	 * We don't know how many segments there are, so we'll probe the
	 * filesystem to find out.
	 */
	for (;;)
	{
		/* See if we need to expand our file segment array. */
		if (nfiles + 1 > capacity)
		{
			capacity *= 2;
			files = repalloc(files, sizeof(File) * capacity);
		}
		/* Try to load a segment. */
		SharedSegmentName(segment_name, name, nfiles);
		files[nfiles] = SharedFileSetOpen(fileset, segment_name);
		if (files[nfiles] <= 0)
			break;
		++nfiles;

		CHECK_FOR_INTERRUPTS();
	}

	/*
	 * If we didn't find any files at all, then no BufFile exists with this
	 * name.
	 */
	if (nfiles == 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open temporary file \"%s\" from BufFile \"%s\": %m",
						segment_name, name)));

	file = makeBufFileCommon(nfiles);
	file->files = files;
	file->readOnly = true;		/* Can't write to files opened this way */
	file->fileset = fileset;
	file->name = pstrdup(name);

	return file;
}