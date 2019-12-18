#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teReqs ;
struct TYPE_3__ {int /*<<< orphan*/  reqs; } ;
typedef  TYPE_1__ TocEntry ;
typedef  int /*<<< orphan*/  DumpId ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 TYPE_1__* getTocEntryByDumpId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

teReqs
TocIDRequired(ArchiveHandle *AH, DumpId id)
{
	TocEntry   *te = getTocEntryByDumpId(AH, id);

	if (!te)
		return 0;

	return te->reqs;
}