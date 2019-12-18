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
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  t_data; } ;
typedef  TYPE_1__* HeapTuple ;
typedef  scalar_t__ HTSV_Result ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ HEAPTUPLE_LIVE ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleSatisfiesVacuum (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tuple_all_visible(HeapTuple tup, TransactionId OldestXmin, Buffer buffer)
{
	HTSV_Result state;
	TransactionId xmin;

	state = HeapTupleSatisfiesVacuum(tup, OldestXmin, buffer);
	if (state != HEAPTUPLE_LIVE)
		return false;			/* all-visible implies live */

	/*
	 * Neither lazy_scan_heap nor heap_page_is_all_visible will mark a page
	 * all-visible unless every tuple is hinted committed. However, those hint
	 * bits could be lost after a crash, so we can't be certain that they'll
	 * be set here.  So just check the xmin.
	 */

	xmin = HeapTupleHeaderGetXmin(tup->t_data);
	if (!TransactionIdPrecedes(xmin, OldestXmin))
		return false;			/* xmin not old enough for all to see */

	return true;
}