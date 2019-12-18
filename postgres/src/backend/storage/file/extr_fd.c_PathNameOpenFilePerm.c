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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {char* fileName; int fileFlags; int fdstate; int /*<<< orphan*/ * resowner; scalar_t__ fileSize; int /*<<< orphan*/  fileMode; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ Vfd ;
typedef  size_t File ;

/* Variables and functions */
 size_t AllocateVfd () ; 
 int /*<<< orphan*/  BasicOpenFilePerm (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeVfd (size_t) ; 
 int /*<<< orphan*/  Insert (size_t) ; 
 int /*<<< orphan*/  LOG ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  ReleaseLruFiles () ; 
 TYPE_1__* VfdCache ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nfile ; 
 char* strdup (char const*) ; 

File
PathNameOpenFilePerm(const char *fileName, int fileFlags, mode_t fileMode)
{
	char	   *fnamecopy;
	File		file;
	Vfd		   *vfdP;

	DO_DB(elog(LOG, "PathNameOpenFilePerm: %s %x %o",
			   fileName, fileFlags, fileMode));

	/*
	 * We need a malloc'd copy of the file name; fail cleanly if no room.
	 */
	fnamecopy = strdup(fileName);
	if (fnamecopy == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));

	file = AllocateVfd();
	vfdP = &VfdCache[file];

	/* Close excess kernel FDs. */
	ReleaseLruFiles();

	vfdP->fd = BasicOpenFilePerm(fileName, fileFlags, fileMode);

	if (vfdP->fd < 0)
	{
		int			save_errno = errno;

		FreeVfd(file);
		free(fnamecopy);
		errno = save_errno;
		return -1;
	}
	++nfile;
	DO_DB(elog(LOG, "PathNameOpenFile: success %d",
			   vfdP->fd));

	Insert(file);

	vfdP->fileName = fnamecopy;
	/* Saved flags are adjusted to be OK for re-opening file */
	vfdP->fileFlags = fileFlags & ~(O_CREAT | O_TRUNC | O_EXCL);
	vfdP->fileMode = fileMode;
	vfdP->fileSize = 0;
	vfdP->fdstate = 0x0;
	vfdP->resowner = NULL;

	return file;
}