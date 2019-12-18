#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t dumpId; scalar_t__ reqs; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_6__ {size_t* tableDataId; TYPE_1__** tocsByDumpId; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
inhibit_data_for_failed_table(ArchiveHandle *AH, TocEntry *te)
{
	pg_log_info("table \"%s\" could not be created, will not restore its data",
				te->tag);

	if (AH->tableDataId[te->dumpId] != 0)
	{
		TocEntry   *ted = AH->tocsByDumpId[AH->tableDataId[te->dumpId]];

		ted->reqs = 0;
	}
}