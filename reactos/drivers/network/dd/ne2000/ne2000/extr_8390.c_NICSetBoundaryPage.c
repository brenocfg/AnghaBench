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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int NextPacket; int PageStart; int PageStop; scalar_t__ IOBase; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PG0_BNRY ; 

__attribute__((used)) static VOID NICSetBoundaryPage(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Sets the boundary page on the adapter to be one less than NextPacket
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    if (Adapter->NextPacket == Adapter->PageStart) {
        NdisRawWritePortUchar(Adapter->IOBase + PG0_BNRY,
            (UCHAR)(Adapter->PageStop - 1));
    } else {
        NdisRawWritePortUchar(Adapter->IOBase + PG0_BNRY,
            (UCHAR)(Adapter->NextPacket - 1));
    }
}