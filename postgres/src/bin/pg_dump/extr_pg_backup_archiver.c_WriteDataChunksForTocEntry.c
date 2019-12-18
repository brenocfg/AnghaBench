#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dataDumperArg; int /*<<< orphan*/  (* dataDumper ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_14__ {TYPE_1__* currToc; int /*<<< orphan*/  (* EndDataPtr ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* StartDataPtr ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* EndBlobsPtr ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* StartBlobsPtr ) (TYPE_2__*,TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  (* StartDataPtrType ) (TYPE_2__*,TYPE_1__*) ;
typedef  int /*<<< orphan*/  (* EndDataPtrType ) (TYPE_2__*,TYPE_1__*) ;
typedef  TYPE_2__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,TYPE_1__*) ; 

void
WriteDataChunksForTocEntry(ArchiveHandle *AH, TocEntry *te)
{
	StartDataPtrType startPtr;
	EndDataPtrType endPtr;

	AH->currToc = te;

	if (strcmp(te->desc, "BLOBS") == 0)
	{
		startPtr = AH->StartBlobsPtr;
		endPtr = AH->EndBlobsPtr;
	}
	else
	{
		startPtr = AH->StartDataPtr;
		endPtr = AH->EndDataPtr;
	}

	if (startPtr != NULL)
		(*startPtr) (AH, te);

	/*
	 * The user-provided DataDumper routine needs to call AH->WriteData
	 */
	te->dataDumper((Archive *) AH, te->dataDumperArg);

	if (endPtr != NULL)
		(*endPtr) (AH, te);

	AH->currToc = NULL;
}