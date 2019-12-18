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
struct TYPE_5__ {void* formatData; } ;
typedef  TYPE_2__ TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/ * ReadStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ pg_malloc0 (int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_ReadExtraToc(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;

	if (tctx == NULL)
	{
		tctx = (lclTocEntry *) pg_malloc0(sizeof(lclTocEntry));
		te->formatData = (void *) tctx;
	}

	tctx->filename = ReadStr(AH);
	if (strlen(tctx->filename) == 0)
	{
		free(tctx->filename);
		tctx->filename = NULL;
	}
}