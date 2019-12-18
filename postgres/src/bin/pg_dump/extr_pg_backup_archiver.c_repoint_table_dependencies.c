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
struct TYPE_4__ {scalar_t__ section; int nDeps; size_t* dependencies; int /*<<< orphan*/  dumpId; int /*<<< orphan*/  dataLength; struct TYPE_4__* next; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_5__ {size_t maxDumpId; scalar_t__* tableDataId; TYPE_1__** tocsByDumpId; TYPE_1__* toc; } ;
typedef  size_t DumpId ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SECTION_POST_DATA ; 
 int /*<<< orphan*/  pg_log_debug (char*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static void
repoint_table_dependencies(ArchiveHandle *AH)
{
	TocEntry   *te;
	int			i;
	DumpId		olddep;

	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		if (te->section != SECTION_POST_DATA)
			continue;
		for (i = 0; i < te->nDeps; i++)
		{
			olddep = te->dependencies[i];
			if (olddep <= AH->maxDumpId &&
				AH->tableDataId[olddep] != 0)
			{
				DumpId		tabledataid = AH->tableDataId[olddep];
				TocEntry   *tabledatate = AH->tocsByDumpId[tabledataid];

				te->dependencies[i] = tabledataid;
				te->dataLength = Max(te->dataLength, tabledatate->dataLength);
				pg_log_debug("transferring dependency %d -> %d to %d",
							 te->dumpId, olddep, tabledataid);
			}
		}
	}
}