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
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_2__ {scalar_t__ rs_nblocks; } ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  TYPE_1__* HeapScanDesc ;

/* Variables and functions */
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
heapam_tuple_tid_valid(TableScanDesc scan, ItemPointer tid)
{
	HeapScanDesc hscan = (HeapScanDesc) scan;

	return ItemPointerIsValid(tid) &&
		ItemPointerGetBlockNumber(tid) < hscan->rs_nblocks;
}