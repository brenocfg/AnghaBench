#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  SampleScanState ;

/* Variables and functions */

__attribute__((used)) static bool
SampleRecheck(SampleScanState *node, TupleTableSlot *slot)
{
	/*
	 * No need to recheck for SampleScan, since like SeqScan we don't pass any
	 * checkable keys to heap_beginscan.
	 */
	return true;
}