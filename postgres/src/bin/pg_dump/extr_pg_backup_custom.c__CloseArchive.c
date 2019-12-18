#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_9__ {scalar_t__ hasSeek; int /*<<< orphan*/  dataStart; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_10__ {scalar_t__ mode; int /*<<< orphan*/ * FH; scalar_t__ fSpec; scalar_t__ dosync; scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WriteDataChunks (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteHead (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteToc (TYPE_2__*) ; 
 int /*<<< orphan*/  _getFilePos (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ archModeWrite ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_fname (scalar_t__,int) ; 
 int /*<<< orphan*/  ftello (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_CloseArchive(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	pgoff_t		tpos;

	if (AH->mode == archModeWrite)
	{
		WriteHead(AH);
		/* Remember TOC's seek position for use below */
		tpos = ftello(AH->FH);
		if (tpos < 0 && ctx->hasSeek)
			fatal("could not determine seek position in archive file: %m");
		WriteToc(AH);
		ctx->dataStart = _getFilePos(AH, ctx);
		WriteDataChunks(AH, NULL);

		/*
		 * If possible, re-write the TOC in order to update the data offset
		 * information.  This is not essential, as pg_restore can cope in most
		 * cases without it; but it can make pg_restore significantly faster
		 * in some situations (especially parallel restore).
		 */
		if (ctx->hasSeek &&
			fseeko(AH->FH, tpos, SEEK_SET) == 0)
			WriteToc(AH);
	}

	if (fclose(AH->FH) != 0)
		fatal("could not close archive file: %m");

	/* Sync the output file if one is defined */
	if (AH->dosync && AH->mode == archModeWrite && AH->fSpec)
		(void) fsync_fname(AH->fSpec, false);

	AH->FH = NULL;
}