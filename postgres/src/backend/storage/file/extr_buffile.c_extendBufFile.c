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
struct TYPE_4__ {int numFiles; scalar_t__* files; int /*<<< orphan*/  isInterXact; int /*<<< orphan*/ * fileset; int /*<<< orphan*/  resowner; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  scalar_t__ File ;
typedef  TYPE_1__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 scalar_t__ MakeNewSharedSegment (TYPE_1__*,int) ; 
 scalar_t__ OpenTemporaryFile (int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (scalar_t__*,int) ; 

__attribute__((used)) static void
extendBufFile(BufFile *file)
{
	File		pfile;
	ResourceOwner oldowner;

	/* Be sure to associate the file with the BufFile's resource owner */
	oldowner = CurrentResourceOwner;
	CurrentResourceOwner = file->resowner;

	if (file->fileset == NULL)
		pfile = OpenTemporaryFile(file->isInterXact);
	else
		pfile = MakeNewSharedSegment(file, file->numFiles);

	Assert(pfile >= 0);

	CurrentResourceOwner = oldowner;

	file->files = (File *) repalloc(file->files,
									(file->numFiles + 1) * sizeof(File));
	file->files[file->numFiles] = pfile;
	file->numFiles++;
}