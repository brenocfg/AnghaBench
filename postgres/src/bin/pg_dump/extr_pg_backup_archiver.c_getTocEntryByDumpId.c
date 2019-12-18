#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_4__ {size_t maxDumpId; int /*<<< orphan*/ ** tocsByDumpId; } ;
typedef  size_t DumpId ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  buildTocEntryArrays (TYPE_1__*) ; 

TocEntry *
getTocEntryByDumpId(ArchiveHandle *AH, DumpId id)
{
	/* build index arrays if we didn't already */
	if (AH->tocsByDumpId == NULL)
		buildTocEntryArrays(AH);

	if (id > 0 && id <= AH->maxDumpId)
		return AH->tocsByDumpId[id];

	return NULL;
}