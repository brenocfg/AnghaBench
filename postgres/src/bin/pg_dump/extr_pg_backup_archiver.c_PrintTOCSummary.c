#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ teSection ;
typedef  int /*<<< orphan*/  stamp_str ;
struct TYPE_14__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  tableoid; } ;
struct TYPE_15__ {scalar_t__ section; scalar_t__ nDeps; int /*<<< orphan*/ * dependencies; int /*<<< orphan*/  desc; TYPE_2__ catalogId; int /*<<< orphan*/  dumpId; int /*<<< orphan*/  owner; int /*<<< orphan*/  namespace; int /*<<< orphan*/  tag; struct TYPE_15__* next; } ;
typedef  TYPE_3__ TocEntry ;
struct TYPE_13__ {TYPE_4__* ropt; } ;
struct TYPE_17__ {int format; TYPE_3__* toc; int /*<<< orphan*/  archiveDumpVersion; int /*<<< orphan*/  archiveRemoteVersion; scalar_t__ offSize; scalar_t__ intSize; int /*<<< orphan*/  version; int /*<<< orphan*/  compression; int /*<<< orphan*/  tocCount; int /*<<< orphan*/  archdbname; int /*<<< orphan*/  createDate; TYPE_1__ public; } ;
struct TYPE_16__ {scalar_t__ filename; scalar_t__ strict_names; scalar_t__ verbose; } ;
typedef  TYPE_4__ RestoreOptions ;
typedef  int /*<<< orphan*/  OutputContext ;
typedef  TYPE_5__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCHIVE_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCHIVE_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGDUMP_STRFTIME_FMT ; 
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
 int /*<<< orphan*/  RestoreOutput (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SECTION_NONE ; 
 scalar_t__ SECTION_PRE_DATA ; 
 int /*<<< orphan*/  SaveOutput (TYPE_5__*) ; 
 int /*<<< orphan*/  SetOutput (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrictNamesCheck (TYPE_4__*) ; 
 int _tocEntryRequired (TYPE_3__*,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_5__*,char*,...) ; 
#define  archCustom 130 
#define  archDirectory 129 
#define  archTar 128 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 char* sanitize_line (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strftime (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PrintTOCSummary(Archive *AHX)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	RestoreOptions *ropt = AH->public.ropt;
	TocEntry   *te;
	teSection	curSection;
	OutputContext sav;
	const char *fmtName;
	char		stamp_str[64];

	sav = SaveOutput(AH);
	if (ropt->filename)
		SetOutput(AH, ropt->filename, 0 /* no compression */ );

	if (strftime(stamp_str, sizeof(stamp_str), PGDUMP_STRFTIME_FMT,
				 localtime(&AH->createDate)) == 0)
		strcpy(stamp_str, "[unknown]");

	ahprintf(AH, ";\n; Archive created at %s\n", stamp_str);
	ahprintf(AH, ";     dbname: %s\n;     TOC Entries: %d\n;     Compression: %d\n",
			 sanitize_line(AH->archdbname, false),
			 AH->tocCount, AH->compression);

	switch (AH->format)
	{
		case archCustom:
			fmtName = "CUSTOM";
			break;
		case archDirectory:
			fmtName = "DIRECTORY";
			break;
		case archTar:
			fmtName = "TAR";
			break;
		default:
			fmtName = "UNKNOWN";
	}

	ahprintf(AH, ";     Dump Version: %d.%d-%d\n",
			 ARCHIVE_MAJOR(AH->version), ARCHIVE_MINOR(AH->version), ARCHIVE_REV(AH->version));
	ahprintf(AH, ";     Format: %s\n", fmtName);
	ahprintf(AH, ";     Integer: %d bytes\n", (int) AH->intSize);
	ahprintf(AH, ";     Offset: %d bytes\n", (int) AH->offSize);
	if (AH->archiveRemoteVersion)
		ahprintf(AH, ";     Dumped from database version: %s\n",
				 AH->archiveRemoteVersion);
	if (AH->archiveDumpVersion)
		ahprintf(AH, ";     Dumped by pg_dump version: %s\n",
				 AH->archiveDumpVersion);

	ahprintf(AH, ";\n;\n; Selected TOC Entries:\n;\n");

	curSection = SECTION_PRE_DATA;
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		if (te->section != SECTION_NONE)
			curSection = te->section;
		if (ropt->verbose ||
			(_tocEntryRequired(te, curSection, AH) & (REQ_SCHEMA | REQ_DATA)) != 0)
		{
			char	   *sanitized_name;
			char	   *sanitized_schema;
			char	   *sanitized_owner;

			/*
			 */
			sanitized_name = sanitize_line(te->tag, false);
			sanitized_schema = sanitize_line(te->namespace, true);
			sanitized_owner = sanitize_line(te->owner, false);

			ahprintf(AH, "%d; %u %u %s %s %s %s\n", te->dumpId,
					 te->catalogId.tableoid, te->catalogId.oid,
					 te->desc, sanitized_schema, sanitized_name,
					 sanitized_owner);

			free(sanitized_name);
			free(sanitized_schema);
			free(sanitized_owner);
		}
		if (ropt->verbose && te->nDeps > 0)
		{
			int			i;

			ahprintf(AH, ";\tdepends on:");
			for (i = 0; i < te->nDeps; i++)
				ahprintf(AH, " %d", te->dependencies[i]);
			ahprintf(AH, "\n");
		}
	}

	/* Enforce strict names checking */
	if (ropt->strict_names)
		StrictNamesCheck(ropt);

	if (ropt->filename)
		RestoreOutput(AH, sav);
}