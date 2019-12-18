#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int isSpecialScript; int /*<<< orphan*/  tarFH; int /*<<< orphan*/ * scriptTH; int /*<<< orphan*/ * FH; } ;
typedef  TYPE_2__ lclContext ;
struct TYPE_16__ {int verbose; TYPE_3__* ropt; int /*<<< orphan*/ * dopt; } ;
struct TYPE_19__ {scalar_t__ mode; int /*<<< orphan*/ * FH; scalar_t__ fSpec; scalar_t__ dosync; TYPE_1__ public; int /*<<< orphan*/  CustomOutPtr; scalar_t__ formatData; } ;
struct TYPE_18__ {int dropSchema; int suppressDumpWarnings; int /*<<< orphan*/ * superuser; scalar_t__ compression; int /*<<< orphan*/ * filename; } ;
typedef  int /*<<< orphan*/  TAR_MEMBER ;
typedef  TYPE_3__ RestoreOptions ;
typedef  int /*<<< orphan*/  DumpOptions ;
typedef  TYPE_4__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 scalar_t__ EOF ; 
 TYPE_3__* NewRestoreOptions () ; 
 int /*<<< orphan*/  RestoreArchive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetArchiveOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  WRITE_ERROR_EXIT ; 
 int /*<<< orphan*/  WriteDataChunks (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteHead (TYPE_4__*) ; 
 int /*<<< orphan*/  WriteToc (TYPE_4__*) ; 
 int /*<<< orphan*/  _scriptOut ; 
 scalar_t__ archModeWrite ; 
 scalar_t__ fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_fname (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  tarClose (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tarOpen (TYPE_4__*,char*,char) ; 
 int /*<<< orphan*/  tarPrintf (TYPE_4__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
_CloseArchive(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	TAR_MEMBER *th;
	RestoreOptions *ropt;
	RestoreOptions *savRopt;
	DumpOptions *savDopt;
	int			savVerbose,
				i;

	if (AH->mode == archModeWrite)
	{
		/*
		 * Write the Header & TOC to the archive FIRST
		 */
		th = tarOpen(AH, "toc.dat", 'w');
		ctx->FH = th;
		WriteHead(AH);
		WriteToc(AH);
		tarClose(AH, th);		/* Not needed any more */

		/*
		 * Now send the data (tables & blobs)
		 */
		WriteDataChunks(AH, NULL);

		/*
		 * Now this format wants to append a script which does a full restore
		 * if the files have been extracted.
		 */
		th = tarOpen(AH, "restore.sql", 'w');

		tarPrintf(AH, th, "--\n"
				  "-- NOTE:\n"
				  "--\n"
				  "-- File paths need to be edited. Search for $$PATH$$ and\n"
				  "-- replace it with the path to the directory containing\n"
				  "-- the extracted data files.\n"
				  "--\n");

		AH->CustomOutPtr = _scriptOut;

		ctx->isSpecialScript = 1;
		ctx->scriptTH = th;

		ropt = NewRestoreOptions();
		memcpy(ropt, AH->public.ropt, sizeof(RestoreOptions));
		ropt->filename = NULL;
		ropt->dropSchema = 1;
		ropt->compression = 0;
		ropt->superuser = NULL;
		ropt->suppressDumpWarnings = true;

		savDopt = AH->public.dopt;
		savRopt = AH->public.ropt;

		SetArchiveOptions((Archive *) AH, NULL, ropt);

		savVerbose = AH->public.verbose;
		AH->public.verbose = 0;

		RestoreArchive((Archive *) AH);

		SetArchiveOptions((Archive *) AH, savDopt, savRopt);

		AH->public.verbose = savVerbose;

		tarClose(AH, th);

		ctx->isSpecialScript = 0;

		/*
		 * EOF marker for tar files is two blocks of NULLs.
		 */
		for (i = 0; i < 512 * 2; i++)
		{
			if (fputc(0, ctx->tarFH) == EOF)
				WRITE_ERROR_EXIT;
		}

		/* Sync the output file if one is defined */
		if (AH->dosync && AH->fSpec)
			(void) fsync_fname(AH->fSpec, false);
	}

	AH->FH = NULL;
}