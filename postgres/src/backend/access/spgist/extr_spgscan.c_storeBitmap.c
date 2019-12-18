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
struct TYPE_3__ {int /*<<< orphan*/  ntids; int /*<<< orphan*/  tbm; } ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
storeBitmap(SpGistScanOpaque so, ItemPointer heapPtr,
			Datum leafValue, bool isnull, bool recheck, bool recheckDistances,
			double *distances)
{
	Assert(!recheckDistances && !distances);
	tbm_add_tuples(so->tbm, heapPtr, 1, recheck);
	so->ntids++;
}