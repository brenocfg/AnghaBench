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
struct TYPE_6__ {int /*<<< orphan*/ * TH; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_7__ {int dumpId; void* formatData; int /*<<< orphan*/ * dataDumper; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_8__ {scalar_t__ compression; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int K_STD_BUF_SIZE ; 
 scalar_t__ pg_malloc0 (int) ; 
 int /*<<< orphan*/ * pg_strdup (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
_ArchiveEntry(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *ctx;
	char		fn[K_STD_BUF_SIZE];

	ctx = (lclTocEntry *) pg_malloc0(sizeof(lclTocEntry));
	if (te->dataDumper != NULL)
	{
#ifdef HAVE_LIBZ
		if (AH->compression == 0)
			sprintf(fn, "%d.dat", te->dumpId);
		else
			sprintf(fn, "%d.dat.gz", te->dumpId);
#else
		sprintf(fn, "%d.dat", te->dumpId);
#endif
		ctx->filename = pg_strdup(fn);
	}
	else
	{
		ctx->filename = NULL;
		ctx->TH = NULL;
	}
	te->formatData = (void *) ctx;
}