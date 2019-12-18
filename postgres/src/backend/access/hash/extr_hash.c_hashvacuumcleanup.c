#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 

IndexBulkDeleteResult *
hashvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	Relation	rel = info->index;
	BlockNumber num_pages;

	/* If hashbulkdelete wasn't called, return NULL signifying no change */
	/* Note: this covers the analyze_only case too */
	if (stats == NULL)
		return NULL;

	/* update statistics */
	num_pages = RelationGetNumberOfBlocks(rel);
	stats->num_pages = num_pages;

	return stats;
}