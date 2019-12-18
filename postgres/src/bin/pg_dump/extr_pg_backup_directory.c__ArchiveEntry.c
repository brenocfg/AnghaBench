#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_5__ {int dumpId; void* formatData; scalar_t__ dataDumper; int /*<<< orphan*/  desc; } ;
typedef  TYPE_2__ TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 scalar_t__ pg_malloc0 (int) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
_ArchiveEntry(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *tctx;
	char		fn[MAXPGPATH];

	tctx = (lclTocEntry *) pg_malloc0(sizeof(lclTocEntry));
	if (strcmp(te->desc, "BLOBS") == 0)
		tctx->filename = pg_strdup("blobs.toc");
	else if (te->dataDumper)
	{
		snprintf(fn, MAXPGPATH, "%d.dat", te->dumpId);
		tctx->filename = pg_strdup(fn);
	}
	else
		tctx->filename = NULL;

	te->formatData = (void *) tctx;
}