#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* directory; int /*<<< orphan*/ * blobsTocFH; } ;
typedef  TYPE_3__ lclContext ;
struct TYPE_13__ {TYPE_1__* ropt; } ;
struct TYPE_15__ {TYPE_2__ public; scalar_t__ formatData; } ;
struct TYPE_12__ {int /*<<< orphan*/  dropSchema; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EndRestoreBlob (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndRestoreBlobs (TYPE_4__*) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  StartRestoreBlob (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartRestoreBlobs (TYPE_4__*) ; 
 int /*<<< orphan*/  _PrintFileData (TYPE_4__*,char*) ; 
 scalar_t__ cfclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cfgets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * cfopen_read (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char*,...) ; 
 int /*<<< orphan*/  setFilePath (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
_LoadBlobs(ArchiveHandle *AH)
{
	Oid			oid;
	lclContext *ctx = (lclContext *) AH->formatData;
	char		fname[MAXPGPATH];
	char		line[MAXPGPATH];

	StartRestoreBlobs(AH);

	setFilePath(AH, fname, "blobs.toc");

	ctx->blobsTocFH = cfopen_read(fname, PG_BINARY_R);

	if (ctx->blobsTocFH == NULL)
		fatal("could not open large object TOC file \"%s\" for input: %m",
			  fname);

	/* Read the blobs TOC file line-by-line, and process each blob */
	while ((cfgets(ctx->blobsTocFH, line, MAXPGPATH)) != NULL)
	{
		char		fname[MAXPGPATH];
		char		path[MAXPGPATH];

		/* Can't overflow because line and fname are the same length. */
		if (sscanf(line, "%u %s\n", &oid, fname) != 2)
			fatal("invalid line in large object TOC file \"%s\": \"%s\"",
				  fname, line);

		StartRestoreBlob(AH, oid, AH->public.ropt->dropSchema);
		snprintf(path, MAXPGPATH, "%s/%s", ctx->directory, fname);
		_PrintFileData(AH, path);
		EndRestoreBlob(AH, oid);
	}
	if (!cfeof(ctx->blobsTocFH))
		fatal("error reading large object TOC file \"%s\"",
			  fname);

	if (cfclose(ctx->blobsTocFH) != 0)
		fatal("could not close large object TOC file \"%s\": %m",
			  fname);

	ctx->blobsTocFH = NULL;

	EndRestoreBlobs(AH);
}