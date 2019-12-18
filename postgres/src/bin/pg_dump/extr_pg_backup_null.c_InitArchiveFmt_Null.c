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
struct TYPE_3__ {scalar_t__ mode; void* lo_buf; int /*<<< orphan*/  lo_buf_size; int /*<<< orphan*/ * DeClonePtr; int /*<<< orphan*/ * ClonePtr; int /*<<< orphan*/  EndBlobsPtr; int /*<<< orphan*/  EndBlobPtr; int /*<<< orphan*/  StartBlobPtr; int /*<<< orphan*/  StartBlobsPtr; int /*<<< orphan*/  PrintTocDataPtr; int /*<<< orphan*/ * ReopenPtr; int /*<<< orphan*/  ClosePtr; int /*<<< orphan*/  WriteBufPtr; int /*<<< orphan*/  WriteBytePtr; int /*<<< orphan*/  EndDataPtr; int /*<<< orphan*/  WriteDataPtr; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  LOBBUFSIZE ; 
 int /*<<< orphan*/  _CloseArchive ; 
 int /*<<< orphan*/  _EndBlob ; 
 int /*<<< orphan*/  _EndBlobs ; 
 int /*<<< orphan*/  _EndData ; 
 int /*<<< orphan*/  _PrintTocData ; 
 int /*<<< orphan*/  _StartBlob ; 
 int /*<<< orphan*/  _StartBlobs ; 
 int /*<<< orphan*/  _WriteBuf ; 
 int /*<<< orphan*/  _WriteByte ; 
 int /*<<< orphan*/  _WriteData ; 
 scalar_t__ archModeRead ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ pg_malloc (int /*<<< orphan*/ ) ; 

void
InitArchiveFmt_Null(ArchiveHandle *AH)
{
	/* Assuming static functions, this can be copied for each format. */
	AH->WriteDataPtr = _WriteData;
	AH->EndDataPtr = _EndData;
	AH->WriteBytePtr = _WriteByte;
	AH->WriteBufPtr = _WriteBuf;
	AH->ClosePtr = _CloseArchive;
	AH->ReopenPtr = NULL;
	AH->PrintTocDataPtr = _PrintTocData;

	AH->StartBlobsPtr = _StartBlobs;
	AH->StartBlobPtr = _StartBlob;
	AH->EndBlobPtr = _EndBlob;
	AH->EndBlobsPtr = _EndBlobs;
	AH->ClonePtr = NULL;
	AH->DeClonePtr = NULL;

	/* Initialize LO buffering */
	AH->lo_buf_size = LOBBUFSIZE;
	AH->lo_buf = (void *) pg_malloc(LOBBUFSIZE);

	/*
	 * Now prevent reading...
	 */
	if (AH->mode == archModeRead)
		fatal("this format cannot be read");
}