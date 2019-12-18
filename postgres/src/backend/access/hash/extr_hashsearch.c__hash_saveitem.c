#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* items; } ;
struct TYPE_10__ {TYPE_1__ currPos; } ;
struct TYPE_9__ {int /*<<< orphan*/  indexOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_2__* IndexTuple ;
typedef  TYPE_3__ HashScanPosItem ;
typedef  TYPE_4__* HashScanOpaque ;

/* Variables and functions */

__attribute__((used)) static inline void
_hash_saveitem(HashScanOpaque so, int itemIndex,
			   OffsetNumber offnum, IndexTuple itup)
{
	HashScanPosItem *currItem = &so->currPos.items[itemIndex];

	currItem->heapTid = itup->t_tid;
	currItem->indexOffset = offnum;
}