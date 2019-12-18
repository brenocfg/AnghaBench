#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  directory; int /*<<< orphan*/  pstate; int /*<<< orphan*/ * dataFH; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  cfp ;
struct TYPE_11__ {scalar_t__ mode; int /*<<< orphan*/ * FH; scalar_t__ dosync; int /*<<< orphan*/  format; scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/  ParallelBackupEnd (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParallelBackupStart (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteDataChunks (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteHead (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteToc (TYPE_2__*) ; 
 int /*<<< orphan*/  archDirectory ; 
 scalar_t__ archModeWrite ; 
 int /*<<< orphan*/  archTar ; 
 scalar_t__ cfclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cfopen_write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fsync_dir_recurse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setFilePath (TYPE_2__*,char*,char*) ; 

__attribute__((used)) static void
_CloseArchive(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	if (AH->mode == archModeWrite)
	{
		cfp		   *tocFH;
		char		fname[MAXPGPATH];

		setFilePath(AH, fname, "toc.dat");

		/* this will actually fork the processes for a parallel backup */
		ctx->pstate = ParallelBackupStart(AH);

		/* The TOC is always created uncompressed */
		tocFH = cfopen_write(fname, PG_BINARY_W, 0);
		if (tocFH == NULL)
			fatal("could not open output file \"%s\": %m", fname);
		ctx->dataFH = tocFH;

		/*
		 * Write 'tar' in the format field of the toc.dat file. The directory
		 * is compatible with 'tar', so there's no point having a different
		 * format code for it.
		 */
		AH->format = archTar;
		WriteHead(AH);
		AH->format = archDirectory;
		WriteToc(AH);
		if (cfclose(tocFH) != 0)
			fatal("could not close TOC file: %m");
		WriteDataChunks(AH, ctx->pstate);

		ParallelBackupEnd(AH, ctx->pstate);

		/*
		 * In directory mode, there is no need to sync all the entries
		 * individually. Just recurse once through all the files generated.
		 */
		if (AH->dosync)
			fsync_dir_recurse(ctx->directory);
	}
	AH->FH = NULL;
}