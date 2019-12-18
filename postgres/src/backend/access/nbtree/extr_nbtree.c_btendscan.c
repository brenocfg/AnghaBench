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
struct TYPE_7__ {scalar_t__ numKilled; int markItemIndex; struct TYPE_7__* currTuples; struct TYPE_7__* killedItems; int /*<<< orphan*/ * arrayContext; struct TYPE_7__* keyData; int /*<<< orphan*/  markPos; int /*<<< orphan*/  currPos; } ;
struct TYPE_6__ {int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 scalar_t__ BTScanPosIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTScanPosUnpinIfPinned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_killitems (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

void
btendscan(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;

	/* we aren't holding any read locks, but gotta drop the pins */
	if (BTScanPosIsValid(so->currPos))
	{
		/* Before leaving current page, deal with any killed items */
		if (so->numKilled > 0)
			_bt_killitems(scan);
		BTScanPosUnpinIfPinned(so->currPos);
	}

	so->markItemIndex = -1;
	BTScanPosUnpinIfPinned(so->markPos);

	/* No need to invalidate positions, the RAM is about to be freed. */

	/* Release storage */
	if (so->keyData != NULL)
		pfree(so->keyData);
	/* so->arrayKeyData and so->arrayKeys are in arrayContext */
	if (so->arrayContext != NULL)
		MemoryContextDelete(so->arrayContext);
	if (so->killedItems != NULL)
		pfree(so->killedItems);
	if (so->currTuples != NULL)
		pfree(so->currTuples);
	/* so->markTuples should not be pfree'd, see btrescan */
	pfree(so);
}