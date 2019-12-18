#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ dataLength; scalar_t__ dumpId; } ;
typedef  TYPE_1__ TocEntry ;

/* Variables and functions */

__attribute__((used)) static int
TocEntrySizeCompare(const void *p1, const void *p2)
{
	const TocEntry *te1 = *(const TocEntry *const *) p1;
	const TocEntry *te2 = *(const TocEntry *const *) p2;

	/* Sort by decreasing dataLength */
	if (te1->dataLength > te2->dataLength)
		return -1;
	if (te1->dataLength < te2->dataLength)
		return 1;

	/* For equal dataLengths, sort by dumpId, just to be stable */
	if (te1->dumpId < te2->dumpId)
		return -1;
	if (te1->dumpId > te2->dumpId)
		return 1;

	return 0;
}