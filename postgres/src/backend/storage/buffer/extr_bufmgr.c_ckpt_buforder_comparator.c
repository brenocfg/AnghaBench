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
struct TYPE_2__ {scalar_t__ tsId; scalar_t__ relNode; scalar_t__ forkNum; scalar_t__ blockNum; } ;
typedef  TYPE_1__ CkptSortItem ;

/* Variables and functions */

__attribute__((used)) static int
ckpt_buforder_comparator(const void *pa, const void *pb)
{
	const CkptSortItem *a = (const CkptSortItem *) pa;
	const CkptSortItem *b = (const CkptSortItem *) pb;

	/* compare tablespace */
	if (a->tsId < b->tsId)
		return -1;
	else if (a->tsId > b->tsId)
		return 1;
	/* compare relation */
	if (a->relNode < b->relNode)
		return -1;
	else if (a->relNode > b->relNode)
		return 1;
	/* compare fork */
	else if (a->forkNum < b->forkNum)
		return -1;
	else if (a->forkNum > b->forkNum)
		return 1;
	/* compare block number */
	else if (a->blockNum < b->blockNum)
		return -1;
	else if (a->blockNum > b->blockNum)
		return 1;
	/* equal page IDs are unlikely, but not impossible */
	return 0;
}