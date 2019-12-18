#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
struct TYPE_6__ {int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ lclTocEntry ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_7__ {int reqs; int dataLength; int /*<<< orphan*/  desc; scalar_t__ formatData; struct TYPE_7__* next; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_8__ {TYPE_2__* toc; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 int REQ_DATA ; 
 int /*<<< orphan*/  setFilePath (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static void
_PrepParallelRestore(ArchiveHandle *AH)
{
	TocEntry   *te;

	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		lclTocEntry *tctx = (lclTocEntry *) te->formatData;
		char		fname[MAXPGPATH];
		struct stat st;

		/*
		 * A dumpable object has set tctx->filename, any other object has not.
		 * (see _ArchiveEntry).
		 */
		if (tctx->filename == NULL)
			continue;

		/* We may ignore items not due to be restored */
		if ((te->reqs & REQ_DATA) == 0)
			continue;

		/*
		 * Stat the file and, if successful, put its size in dataLength.  When
		 * using compression, the physical file size might not be a very good
		 * guide to the amount of work involved in restoring the file, but we
		 * only need an approximate indicator of that.
		 */
		setFilePath(AH, fname, tctx->filename);

		if (stat(fname, &st) == 0)
			te->dataLength = st.st_size;
		else
		{
			/* It might be compressed */
			strlcat(fname, ".gz", sizeof(fname));
			if (stat(fname, &st) == 0)
				te->dataLength = st.st_size;
		}

		/*
		 * If this is the BLOBS entry, what we stat'd was blobs.toc, which
		 * most likely is a lot smaller than the actual blob data.  We don't
		 * have a cheap way to estimate how much smaller, but fortunately it
		 * doesn't matter too much as long as we get the blobs processed
		 * reasonably early.  Arbitrarily scale up by a factor of 1K.
		 */
		if (strcmp(te->desc, "BLOBS") == 0)
			te->dataLength *= 1024;
	}
}