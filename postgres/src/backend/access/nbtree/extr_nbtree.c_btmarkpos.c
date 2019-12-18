#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int itemIndex; } ;
struct TYPE_7__ {int markItemIndex; scalar_t__ numArrayKeys; int /*<<< orphan*/  markPos; TYPE_5__ currPos; } ;
struct TYPE_6__ {int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BTScanPosInvalidate (int /*<<< orphan*/ ) ; 
 scalar_t__ BTScanPosIsValid (TYPE_5__) ; 
 int /*<<< orphan*/  BTScanPosUnpinIfPinned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_mark_array_keys (TYPE_1__*) ; 

void
btmarkpos(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;

	/* There may be an old mark with a pin (but no lock). */
	BTScanPosUnpinIfPinned(so->markPos);

	/*
	 * Just record the current itemIndex.  If we later step to next page
	 * before releasing the marked position, _bt_steppage makes a full copy of
	 * the currPos struct in markPos.  If (as often happens) the mark is moved
	 * before we leave the page, we don't have to do that work.
	 */
	if (BTScanPosIsValid(so->currPos))
		so->markItemIndex = so->currPos.itemIndex;
	else
	{
		BTScanPosInvalidate(so->markPos);
		so->markItemIndex = -1;
	}

	/* Also record the current positions of any array keys */
	if (so->numArrayKeys)
		_bt_mark_array_keys(scan);
}