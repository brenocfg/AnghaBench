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
typedef  int UCHAR ;
struct TYPE_2__ {int tableSize; scalar_t__ table; } ;
typedef  int /*<<< orphan*/  NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int NRC_GOODRET ; 
 int NRC_OSRESNOTAV ; 
 TYPE_1__ gNBTable ; 

__attribute__((used)) static UCHAR nbResizeAdapterTable(UCHAR newSize)
{
    UCHAR ret;

    if (gNBTable.table)
        gNBTable.table = HeapReAlloc(GetProcessHeap(),
         HEAP_ZERO_MEMORY, gNBTable.table,
         newSize * sizeof(NetBIOSAdapter));
    else
        gNBTable.table = HeapAlloc(GetProcessHeap(),
         HEAP_ZERO_MEMORY, newSize * sizeof(NetBIOSAdapter));
    if (gNBTable.table)
    {
        gNBTable.tableSize = newSize;
        ret = NRC_GOODRET;
    }
    else
        ret = NRC_OSRESNOTAV;
    return ret;
}