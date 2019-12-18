#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dataStart; void* hasSeek; scalar_t__ filePos; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_9__ {scalar_t__ mode; void* FH; scalar_t__ fSpec; void* lo_buf; int /*<<< orphan*/  lo_buf_size; void* formatData; int /*<<< orphan*/  WorkerJobRestorePtr; int /*<<< orphan*/ * WorkerJobDumpPtr; int /*<<< orphan*/  DeClonePtr; int /*<<< orphan*/  ClonePtr; int /*<<< orphan*/  PrepParallelRestorePtr; int /*<<< orphan*/  EndBlobsPtr; int /*<<< orphan*/  EndBlobPtr; int /*<<< orphan*/  StartBlobPtr; int /*<<< orphan*/  StartBlobsPtr; int /*<<< orphan*/  PrintExtraTocPtr; int /*<<< orphan*/  WriteExtraTocPtr; int /*<<< orphan*/  ReadExtraTocPtr; int /*<<< orphan*/  PrintTocDataPtr; int /*<<< orphan*/  ReopenPtr; int /*<<< orphan*/  ClosePtr; int /*<<< orphan*/  ReadBufPtr; int /*<<< orphan*/  WriteBufPtr; int /*<<< orphan*/  ReadBytePtr; int /*<<< orphan*/  WriteBytePtr; int /*<<< orphan*/  EndDataPtr; int /*<<< orphan*/  WriteDataPtr; int /*<<< orphan*/  StartDataPtr; int /*<<< orphan*/  ArchiveEntryPtr; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  LOBBUFSIZE ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/  ReadHead (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadToc (TYPE_2__*) ; 
 int /*<<< orphan*/  _ArchiveEntry ; 
 int /*<<< orphan*/  _Clone ; 
 int /*<<< orphan*/  _CloseArchive ; 
 int /*<<< orphan*/  _DeClone ; 
 int /*<<< orphan*/  _EndBlob ; 
 int /*<<< orphan*/  _EndBlobs ; 
 int /*<<< orphan*/  _EndData ; 
 int /*<<< orphan*/  _PrepParallelRestore ; 
 int /*<<< orphan*/  _PrintExtraToc ; 
 int /*<<< orphan*/  _PrintTocData ; 
 int /*<<< orphan*/  _ReadBuf ; 
 int /*<<< orphan*/  _ReadByte ; 
 int /*<<< orphan*/  _ReadExtraToc ; 
 int /*<<< orphan*/  _ReopenArchive ; 
 int /*<<< orphan*/  _StartBlob ; 
 int /*<<< orphan*/  _StartBlobs ; 
 int /*<<< orphan*/  _StartData ; 
 int /*<<< orphan*/  _WorkerJobRestoreCustom ; 
 int /*<<< orphan*/  _WriteBuf ; 
 int /*<<< orphan*/  _WriteByte ; 
 int /*<<< orphan*/  _WriteData ; 
 int /*<<< orphan*/  _WriteExtraToc ; 
 int /*<<< orphan*/  _getFilePos (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ archModeWrite ; 
 void* checkSeek (void*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 void* fopen (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc0 (int) ; 
 void* stdin ; 
 void* stdout ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

void
InitArchiveFmt_Custom(ArchiveHandle *AH)
{
	lclContext *ctx;

	/* Assuming static functions, this can be copied for each format. */
	AH->ArchiveEntryPtr = _ArchiveEntry;
	AH->StartDataPtr = _StartData;
	AH->WriteDataPtr = _WriteData;
	AH->EndDataPtr = _EndData;
	AH->WriteBytePtr = _WriteByte;
	AH->ReadBytePtr = _ReadByte;
	AH->WriteBufPtr = _WriteBuf;
	AH->ReadBufPtr = _ReadBuf;
	AH->ClosePtr = _CloseArchive;
	AH->ReopenPtr = _ReopenArchive;
	AH->PrintTocDataPtr = _PrintTocData;
	AH->ReadExtraTocPtr = _ReadExtraToc;
	AH->WriteExtraTocPtr = _WriteExtraToc;
	AH->PrintExtraTocPtr = _PrintExtraToc;

	AH->StartBlobsPtr = _StartBlobs;
	AH->StartBlobPtr = _StartBlob;
	AH->EndBlobPtr = _EndBlob;
	AH->EndBlobsPtr = _EndBlobs;

	AH->PrepParallelRestorePtr = _PrepParallelRestore;
	AH->ClonePtr = _Clone;
	AH->DeClonePtr = _DeClone;

	/* no parallel dump in the custom archive, only parallel restore */
	AH->WorkerJobDumpPtr = NULL;
	AH->WorkerJobRestorePtr = _WorkerJobRestoreCustom;

	/* Set up a private area. */
	ctx = (lclContext *) pg_malloc0(sizeof(lclContext));
	AH->formatData = (void *) ctx;

	/* Initialize LO buffering */
	AH->lo_buf_size = LOBBUFSIZE;
	AH->lo_buf = (void *) pg_malloc(LOBBUFSIZE);

	ctx->filePos = 0;

	/*
	 * Now open the file
	 */
	if (AH->mode == archModeWrite)
	{
		if (AH->fSpec && strcmp(AH->fSpec, "") != 0)
		{
			AH->FH = fopen(AH->fSpec, PG_BINARY_W);
			if (!AH->FH)
				fatal("could not open output file \"%s\": %m", AH->fSpec);
		}
		else
		{
			AH->FH = stdout;
			if (!AH->FH)
				fatal("could not open output file: %m");
		}

		ctx->hasSeek = checkSeek(AH->FH);
	}
	else
	{
		if (AH->fSpec && strcmp(AH->fSpec, "") != 0)
		{
			AH->FH = fopen(AH->fSpec, PG_BINARY_R);
			if (!AH->FH)
				fatal("could not open input file \"%s\": %m", AH->fSpec);
		}
		else
		{
			AH->FH = stdin;
			if (!AH->FH)
				fatal("could not open input file: %m");
		}

		ctx->hasSeek = checkSeek(AH->FH);

		ReadHead(AH);
		ReadToc(AH);
		ctx->dataStart = _getFilePos(AH, ctx);
	}

}