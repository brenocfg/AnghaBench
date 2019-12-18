#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {scalar_t__ d_name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dataFH; scalar_t__ directory; int /*<<< orphan*/ * blobsTocFH; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  cfp ;
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  format; scalar_t__ fSpec; void* lo_buf; int /*<<< orphan*/  lo_buf_size; void* formatData; int /*<<< orphan*/  WorkerJobDumpPtr; int /*<<< orphan*/  WorkerJobRestorePtr; int /*<<< orphan*/  DeClonePtr; int /*<<< orphan*/  ClonePtr; int /*<<< orphan*/  PrepParallelRestorePtr; int /*<<< orphan*/  EndBlobsPtr; int /*<<< orphan*/  EndBlobPtr; int /*<<< orphan*/  StartBlobPtr; int /*<<< orphan*/  StartBlobsPtr; int /*<<< orphan*/  PrintExtraTocPtr; int /*<<< orphan*/  WriteExtraTocPtr; int /*<<< orphan*/  ReadExtraTocPtr; int /*<<< orphan*/  PrintTocDataPtr; int /*<<< orphan*/  ReopenPtr; int /*<<< orphan*/  ClosePtr; int /*<<< orphan*/  ReadBufPtr; int /*<<< orphan*/  WriteBufPtr; int /*<<< orphan*/  ReadBytePtr; int /*<<< orphan*/  WriteBytePtr; int /*<<< orphan*/  EndDataPtr; int /*<<< orphan*/  WriteDataPtr; int /*<<< orphan*/  StartDataPtr; int /*<<< orphan*/  ArchiveEntryPtr; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  LOBBUFSIZE ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  ReadHead (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadToc (TYPE_2__*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  _WorkerJobDumpDirectory ; 
 int /*<<< orphan*/  _WorkerJobRestoreDirectory ; 
 int /*<<< orphan*/  _WriteBuf ; 
 int /*<<< orphan*/  _WriteByte ; 
 int /*<<< orphan*/  _WriteData ; 
 int /*<<< orphan*/  _WriteExtraToc ; 
 int /*<<< orphan*/  archDirectory ; 
 scalar_t__ archModeWrite ; 
 int /*<<< orphan*/  archTar ; 
 scalar_t__ cfclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cfopen_read (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ mkdir (scalar_t__,int) ; 
 int /*<<< orphan*/ * opendir (scalar_t__) ; 
 scalar_t__ pg_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc0 (int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setFilePath (TYPE_2__*,char*,char*) ; 
 scalar_t__ stat (scalar_t__,struct stat*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

void
InitArchiveFmt_Directory(ArchiveHandle *AH)
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

	AH->WorkerJobRestorePtr = _WorkerJobRestoreDirectory;
	AH->WorkerJobDumpPtr = _WorkerJobDumpDirectory;

	/* Set up our private context */
	ctx = (lclContext *) pg_malloc0(sizeof(lclContext));
	AH->formatData = (void *) ctx;

	ctx->dataFH = NULL;
	ctx->blobsTocFH = NULL;

	/* Initialize LO buffering */
	AH->lo_buf_size = LOBBUFSIZE;
	AH->lo_buf = (void *) pg_malloc(LOBBUFSIZE);

	/*
	 * Now open the TOC file
	 */

	if (!AH->fSpec || strcmp(AH->fSpec, "") == 0)
		fatal("no output directory specified");

	ctx->directory = AH->fSpec;

	if (AH->mode == archModeWrite)
	{
		struct stat st;
		bool		is_empty = false;

		/* we accept an empty existing directory */
		if (stat(ctx->directory, &st) == 0 && S_ISDIR(st.st_mode))
		{
			DIR		   *dir = opendir(ctx->directory);

			if (dir)
			{
				struct dirent *d;

				is_empty = true;
				while (errno = 0, (d = readdir(dir)))
				{
					if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
					{
						is_empty = false;
						break;
					}
				}

				if (errno)
					fatal("could not read directory \"%s\": %m",
						  ctx->directory);

				if (closedir(dir))
					fatal("could not close directory \"%s\": %m",
						  ctx->directory);
			}
		}

		if (!is_empty && mkdir(ctx->directory, 0700) < 0)
			fatal("could not create directory \"%s\": %m",
				  ctx->directory);
	}
	else
	{							/* Read Mode */
		char		fname[MAXPGPATH];
		cfp		   *tocFH;

		setFilePath(AH, fname, "toc.dat");

		tocFH = cfopen_read(fname, PG_BINARY_R);
		if (tocFH == NULL)
			fatal("could not open input file \"%s\": %m", fname);

		ctx->dataFH = tocFH;

		/*
		 * The TOC of a directory format dump shares the format code of the
		 * tar format.
		 */
		AH->format = archTar;
		ReadHead(AH);
		AH->format = archDirectory;
		ReadToc(AH);

		/* Nothing else in the file, so close it again... */
		if (cfclose(tocFH) != 0)
			fatal("could not close TOC file: %m");
		ctx->dataFH = NULL;
	}
}