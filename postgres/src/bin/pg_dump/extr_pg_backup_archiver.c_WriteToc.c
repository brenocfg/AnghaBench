#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tableoid; int oid; } ;
struct TYPE_10__ {int reqs; int dumpId; char* tag; char* desc; int section; char* defn; char* dropStmt; char* copyStmt; char* namespace; char* tablespace; char* tableam; char* owner; int nDeps; int* dependencies; TYPE_1__ catalogId; scalar_t__ dataDumper; struct TYPE_10__* next; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_11__ {int /*<<< orphan*/  (* WriteExtraTocPtr ) (TYPE_3__*,TYPE_2__*) ;TYPE_2__* toc; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
 int REQ_SPECIAL ; 
 int /*<<< orphan*/  WriteInt (TYPE_3__*,int) ; 
 int /*<<< orphan*/  WriteStr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

void
WriteToc(ArchiveHandle *AH)
{
	TocEntry   *te;
	char		workbuf[32];
	int			tocCount;
	int			i;

	/* count entries that will actually be dumped */
	tocCount = 0;
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		if ((te->reqs & (REQ_SCHEMA | REQ_DATA | REQ_SPECIAL)) != 0)
			tocCount++;
	}

	/* printf("%d TOC Entries to save\n", tocCount); */

	WriteInt(AH, tocCount);

	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		if ((te->reqs & (REQ_SCHEMA | REQ_DATA | REQ_SPECIAL)) == 0)
			continue;

		WriteInt(AH, te->dumpId);
		WriteInt(AH, te->dataDumper ? 1 : 0);

		/* OID is recorded as a string for historical reasons */
		sprintf(workbuf, "%u", te->catalogId.tableoid);
		WriteStr(AH, workbuf);
		sprintf(workbuf, "%u", te->catalogId.oid);
		WriteStr(AH, workbuf);

		WriteStr(AH, te->tag);
		WriteStr(AH, te->desc);
		WriteInt(AH, te->section);
		WriteStr(AH, te->defn);
		WriteStr(AH, te->dropStmt);
		WriteStr(AH, te->copyStmt);
		WriteStr(AH, te->namespace);
		WriteStr(AH, te->tablespace);
		WriteStr(AH, te->tableam);
		WriteStr(AH, te->owner);
		WriteStr(AH, "false");

		/* Dump list of dependencies */
		for (i = 0; i < te->nDeps; i++)
		{
			sprintf(workbuf, "%d", te->dependencies[i]);
			WriteStr(AH, workbuf);
		}
		WriteStr(AH, NULL);		/* Terminate List */

		if (AH->WriteExtraTocPtr)
			AH->WriteExtraTocPtr(AH, te);
	}
}