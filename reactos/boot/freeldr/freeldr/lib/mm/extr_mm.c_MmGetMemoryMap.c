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
typedef  int /*<<< orphan*/  PPAGE_LOOKUP_TABLE_ITEM ;
typedef  int /*<<< orphan*/  PFN_NUMBER ;

/* Variables and functions */
 int /*<<< orphan*/  PageLookupTableAddress ; 
 int /*<<< orphan*/  TotalPagesInLookupTable ; 

PPAGE_LOOKUP_TABLE_ITEM MmGetMemoryMap(PFN_NUMBER *NoEntries)
{
    PPAGE_LOOKUP_TABLE_ITEM        RealPageLookupTable = (PPAGE_LOOKUP_TABLE_ITEM)PageLookupTableAddress;

    *NoEntries = TotalPagesInLookupTable;

    return RealPageLookupTable;
}