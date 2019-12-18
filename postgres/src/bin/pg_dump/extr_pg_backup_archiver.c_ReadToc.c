#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char tableoid; char oid; } ;
struct TYPE_16__ {scalar_t__ dumpId; void* desc; char* dependencies; int nDeps; struct TYPE_16__* next; struct TYPE_16__* prev; void* tag; scalar_t__ dataLength; void* owner; void* tableam; void* tablespace; void* namespace; void* copyStmt; void* dropStmt; void* defn; void* section; TYPE_1__ catalogId; void* hadDumper; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_17__ {int tocCount; scalar_t__ maxDumpId; scalar_t__ version; TYPE_2__* toc; int /*<<< orphan*/  (* ReadExtraTocPtr ) (TYPE_3__*,TYPE_2__*) ;} ;
typedef  char DumpId ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 char InvalidOid ; 
 scalar_t__ K_VERS_1_10 ; 
 scalar_t__ K_VERS_1_11 ; 
 scalar_t__ K_VERS_1_14 ; 
 scalar_t__ K_VERS_1_3 ; 
 scalar_t__ K_VERS_1_5 ; 
 scalar_t__ K_VERS_1_6 ; 
 scalar_t__ K_VERS_1_8 ; 
 scalar_t__ K_VERS_1_9 ; 
 void* ReadInt (TYPE_3__*) ; 
 void* ReadStr (TYPE_3__*) ; 
 void* SECTION_DATA ; 
 void* SECTION_NONE ; 
 void* SECTION_POST_DATA ; 
 void* SECTION_PRE_DATA ; 
 int /*<<< orphan*/  fatal (char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,int,scalar_t__,void*,void*) ; 
 int /*<<< orphan*/  pg_log_warning (char*) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_malloc0 (int) ; 
 scalar_t__ pg_realloc (char*,int) ; 
 int /*<<< orphan*/  processEncodingEntry (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  processSearchPathEntry (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  processStdStringsEntry (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,char*) ; 
 scalar_t__ strcmp (void*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

void
ReadToc(ArchiveHandle *AH)
{
	int			i;
	char	   *tmp;
	DumpId	   *deps;
	int			depIdx;
	int			depSize;
	TocEntry   *te;

	AH->tocCount = ReadInt(AH);
	AH->maxDumpId = 0;

	for (i = 0; i < AH->tocCount; i++)
	{
		te = (TocEntry *) pg_malloc0(sizeof(TocEntry));
		te->dumpId = ReadInt(AH);

		if (te->dumpId > AH->maxDumpId)
			AH->maxDumpId = te->dumpId;

		/* Sanity check */
		if (te->dumpId <= 0)
			fatal("entry ID %d out of range -- perhaps a corrupt TOC",
				  te->dumpId);

		te->hadDumper = ReadInt(AH);

		if (AH->version >= K_VERS_1_8)
		{
			tmp = ReadStr(AH);
			sscanf(tmp, "%u", &te->catalogId.tableoid);
			free(tmp);
		}
		else
			te->catalogId.tableoid = InvalidOid;
		tmp = ReadStr(AH);
		sscanf(tmp, "%u", &te->catalogId.oid);
		free(tmp);

		te->tag = ReadStr(AH);
		te->desc = ReadStr(AH);

		if (AH->version >= K_VERS_1_11)
		{
			te->section = ReadInt(AH);
		}
		else
		{
			/*
			 * Rules for pre-8.4 archives wherein pg_dump hasn't classified
			 * the entries into sections.  This list need not cover entry
			 * types added later than 8.4.
			 */
			if (strcmp(te->desc, "COMMENT") == 0 ||
				strcmp(te->desc, "ACL") == 0 ||
				strcmp(te->desc, "ACL LANGUAGE") == 0)
				te->section = SECTION_NONE;
			else if (strcmp(te->desc, "TABLE DATA") == 0 ||
					 strcmp(te->desc, "BLOBS") == 0 ||
					 strcmp(te->desc, "BLOB COMMENTS") == 0)
				te->section = SECTION_DATA;
			else if (strcmp(te->desc, "CONSTRAINT") == 0 ||
					 strcmp(te->desc, "CHECK CONSTRAINT") == 0 ||
					 strcmp(te->desc, "FK CONSTRAINT") == 0 ||
					 strcmp(te->desc, "INDEX") == 0 ||
					 strcmp(te->desc, "RULE") == 0 ||
					 strcmp(te->desc, "TRIGGER") == 0)
				te->section = SECTION_POST_DATA;
			else
				te->section = SECTION_PRE_DATA;
		}

		te->defn = ReadStr(AH);
		te->dropStmt = ReadStr(AH);

		if (AH->version >= K_VERS_1_3)
			te->copyStmt = ReadStr(AH);

		if (AH->version >= K_VERS_1_6)
			te->namespace = ReadStr(AH);

		if (AH->version >= K_VERS_1_10)
			te->tablespace = ReadStr(AH);

		if (AH->version >= K_VERS_1_14)
			te->tableam = ReadStr(AH);

		te->owner = ReadStr(AH);
		if (AH->version < K_VERS_1_9 || strcmp(ReadStr(AH), "true") == 0)
			pg_log_warning("restoring tables WITH OIDS is not supported anymore");

		/* Read TOC entry dependencies */
		if (AH->version >= K_VERS_1_5)
		{
			depSize = 100;
			deps = (DumpId *) pg_malloc(sizeof(DumpId) * depSize);
			depIdx = 0;
			for (;;)
			{
				tmp = ReadStr(AH);
				if (!tmp)
					break;		/* end of list */
				if (depIdx >= depSize)
				{
					depSize *= 2;
					deps = (DumpId *) pg_realloc(deps, sizeof(DumpId) * depSize);
				}
				sscanf(tmp, "%d", &deps[depIdx]);
				free(tmp);
				depIdx++;
			}

			if (depIdx > 0)		/* We have a non-null entry */
			{
				deps = (DumpId *) pg_realloc(deps, sizeof(DumpId) * depIdx);
				te->dependencies = deps;
				te->nDeps = depIdx;
			}
			else
			{
				free(deps);
				te->dependencies = NULL;
				te->nDeps = 0;
			}
		}
		else
		{
			te->dependencies = NULL;
			te->nDeps = 0;
		}
		te->dataLength = 0;

		if (AH->ReadExtraTocPtr)
			AH->ReadExtraTocPtr(AH, te);

		pg_log_debug("read TOC entry %d (ID %d) for %s %s",
					 i, te->dumpId, te->desc, te->tag);

		/* link completed entry into TOC circular list */
		te->prev = AH->toc->prev;
		AH->toc->prev->next = te;
		AH->toc->prev = te;
		te->next = AH->toc;

		/* special processing immediately upon read for some items */
		if (strcmp(te->desc, "ENCODING") == 0)
			processEncodingEntry(AH, te);
		else if (strcmp(te->desc, "STDSTRINGS") == 0)
			processStdStringsEntry(AH, te);
		else if (strcmp(te->desc, "SEARCHPATH") == 0)
			processSearchPathEntry(AH, te);
	}
}