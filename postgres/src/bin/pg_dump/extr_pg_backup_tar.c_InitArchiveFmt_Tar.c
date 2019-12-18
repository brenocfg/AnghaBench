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
struct TYPE_8__ {void* FH; int /*<<< orphan*/ * tarFH; void* hasSeek; scalar_t__ tarFHpos; scalar_t__ isSpecialScript; scalar_t__ filePos; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ compression; scalar_t__ readHeader; scalar_t__ fSpec; void* lo_buf; int /*<<< orphan*/  lo_buf_size; void* formatData; int /*<<< orphan*/ * WorkerJobRestorePtr; int /*<<< orphan*/ * WorkerJobDumpPtr; int /*<<< orphan*/ * DeClonePtr; int /*<<< orphan*/ * ClonePtr; int /*<<< orphan*/  EndBlobsPtr; int /*<<< orphan*/  EndBlobPtr; int /*<<< orphan*/  StartBlobPtr; int /*<<< orphan*/  StartBlobsPtr; int /*<<< orphan*/  PrintExtraTocPtr; int /*<<< orphan*/  WriteExtraTocPtr; int /*<<< orphan*/  ReadExtraTocPtr; int /*<<< orphan*/  PrintTocDataPtr; int /*<<< orphan*/ * ReopenPtr; int /*<<< orphan*/  ClosePtr; int /*<<< orphan*/  ReadBufPtr; int /*<<< orphan*/  WriteBufPtr; int /*<<< orphan*/  ReadBytePtr; int /*<<< orphan*/  WriteBytePtr; int /*<<< orphan*/  EndDataPtr; int /*<<< orphan*/  WriteDataPtr; int /*<<< orphan*/  StartDataPtr; int /*<<< orphan*/  ArchiveEntryPtr; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  LOBBUFSIZE ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/  ReadHead (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadToc (TYPE_2__*) ; 
 int /*<<< orphan*/  _ArchiveEntry ; 
 int /*<<< orphan*/  _CloseArchive ; 
 int /*<<< orphan*/  _EndBlob ; 
 int /*<<< orphan*/  _EndBlobs ; 
 int /*<<< orphan*/  _EndData ; 
 int /*<<< orphan*/  _PrintExtraToc ; 
 int /*<<< orphan*/  _PrintTocData ; 
 int /*<<< orphan*/  _ReadBuf ; 
 int /*<<< orphan*/  _ReadByte ; 
 int /*<<< orphan*/  _ReadExtraToc ; 
 int /*<<< orphan*/  _StartBlob ; 
 int /*<<< orphan*/  _StartBlobs ; 
 int /*<<< orphan*/  _StartData ; 
 int /*<<< orphan*/  _WriteBuf ; 
 int /*<<< orphan*/  _WriteByte ; 
 int /*<<< orphan*/  _WriteData ; 
 int /*<<< orphan*/  _WriteExtraToc ; 
 scalar_t__ archModeWrite ; 
 void* checkSeek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 void* fopen (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc0 (int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  tarClose (TYPE_2__*,void*) ; 
 scalar_t__ tarOpen (TYPE_2__*,char*,char) ; 

void
InitArchiveFmt_Tar(ArchiveHandle *AH)
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
	AH->ReopenPtr = NULL;
	AH->PrintTocDataPtr = _PrintTocData;
	AH->ReadExtraTocPtr = _ReadExtraToc;
	AH->WriteExtraTocPtr = _WriteExtraToc;
	AH->PrintExtraTocPtr = _PrintExtraToc;

	AH->StartBlobsPtr = _StartBlobs;
	AH->StartBlobPtr = _StartBlob;
	AH->EndBlobPtr = _EndBlob;
	AH->EndBlobsPtr = _EndBlobs;
	AH->ClonePtr = NULL;
	AH->DeClonePtr = NULL;

	AH->WorkerJobDumpPtr = NULL;
	AH->WorkerJobRestorePtr = NULL;

	/*
	 * Set up some special context used in compressing data.
	 */
	ctx = (lclContext *) pg_malloc0(sizeof(lclContext));
	AH->formatData = (void *) ctx;
	ctx->filePos = 0;
	ctx->isSpecialScript = 0;

	/* Initialize LO buffering */
	AH->lo_buf_size = LOBBUFSIZE;
	AH->lo_buf = (void *) pg_malloc(LOBBUFSIZE);

	/*
	 * Now open the tar file, and load the TOC if we're in read mode.
	 */
	if (AH->mode == archModeWrite)
	{
		if (AH->fSpec && strcmp(AH->fSpec, "") != 0)
		{
			ctx->tarFH = fopen(AH->fSpec, PG_BINARY_W);
			if (ctx->tarFH == NULL)
				fatal("could not open TOC file \"%s\" for output: %m",
					  AH->fSpec);
		}
		else
		{
			ctx->tarFH = stdout;
			if (ctx->tarFH == NULL)
				fatal("could not open TOC file for output: %m");
		}

		ctx->tarFHpos = 0;

		/*
		 * Make unbuffered since we will dup() it, and the buffers screw each
		 * other
		 */
		/* setvbuf(ctx->tarFH, NULL, _IONBF, 0); */

		ctx->hasSeek = checkSeek(ctx->tarFH);

		/*
		 * We don't support compression because reading the files back is not
		 * possible since gzdopen uses buffered IO which totally screws file
		 * positioning.
		 */
		if (AH->compression != 0)
			fatal("compression is not supported by tar archive format");
	}
	else
	{							/* Read Mode */
		if (AH->fSpec && strcmp(AH->fSpec, "") != 0)
		{
			ctx->tarFH = fopen(AH->fSpec, PG_BINARY_R);
			if (ctx->tarFH == NULL)
				fatal("could not open TOC file \"%s\" for input: %m",
					  AH->fSpec);
		}
		else
		{
			ctx->tarFH = stdin;
			if (ctx->tarFH == NULL)
				fatal("could not open TOC file for input: %m");
		}

		/*
		 * Make unbuffered since we will dup() it, and the buffers screw each
		 * other
		 */
		/* setvbuf(ctx->tarFH, NULL, _IONBF, 0); */

		ctx->tarFHpos = 0;

		ctx->hasSeek = checkSeek(ctx->tarFH);

		/*
		 * Forcibly unmark the header as read since we use the lookahead
		 * buffer
		 */
		AH->readHeader = 0;

		ctx->FH = (void *) tarOpen(AH, "toc.dat", 'r');
		ReadHead(AH);
		ReadToc(AH);
		tarClose(AH, ctx->FH);	/* Nothing else in the file... */
	}
}