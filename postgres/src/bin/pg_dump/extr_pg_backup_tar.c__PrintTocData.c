#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_12__ {scalar_t__ isSpecialScript; } ;
typedef  TYPE_2__ lclContext ;
struct TYPE_13__ {scalar_t__ desc; scalar_t__ copyStmt; scalar_t__ formatData; } ;
typedef  TYPE_3__ TocEntry ;
struct TYPE_14__ {scalar_t__ formatData; } ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  _LoadBlobs (TYPE_4__*) ; 
 int /*<<< orphan*/  _PrintFileData (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahprintf (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  ahwrite (scalar_t__,int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  fatal (char*,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strlen (scalar_t__) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void
_PrintTocData(ArchiveHandle *AH, TocEntry *te)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;
	int			pos1;

	if (!tctx->filename)
		return;

	/*
	 * If we're writing the special restore.sql script, emit a suitable
	 * command to include each table's data from the corresponding file.
	 *
	 * In the COPY case this is a bit klugy because the regular COPY command
	 * was already printed before we get control.
	 */
	if (ctx->isSpecialScript)
	{
		if (te->copyStmt)
		{
			/* Abort the COPY FROM stdin */
			ahprintf(AH, "\\.\n");

			/*
			 * The COPY statement should look like "COPY ... FROM stdin;\n",
			 * see dumpTableData().
			 */
			pos1 = (int) strlen(te->copyStmt) - 13;
			if (pos1 < 6 || strncmp(te->copyStmt, "COPY ", 5) != 0 ||
				strcmp(te->copyStmt + pos1, " FROM stdin;\n") != 0)
				fatal("unexpected COPY statement syntax: \"%s\"",
					  te->copyStmt);

			/* Emit all but the FROM part ... */
			ahwrite(te->copyStmt, 1, pos1, AH);
			/* ... and insert modified FROM */
			ahprintf(AH, " FROM '$$PATH$$/%s';\n\n", tctx->filename);
		}
		else
		{
			/* --inserts mode, no worries, just include the data file */
			ahprintf(AH, "\\i $$PATH$$/%s\n\n", tctx->filename);
		}

		return;
	}

	if (strcmp(te->desc, "BLOBS") == 0)
		_LoadBlobs(AH);
	else
		_PrintFileData(AH, tctx->filename);
}