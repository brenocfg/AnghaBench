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
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  MissedPackets; scalar_t__ IOBase; int /*<<< orphan*/  CrcErrors; int /*<<< orphan*/  FrameAlignmentErrors; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NdisRawReadPortUchar (scalar_t__,scalar_t__*) ; 
 scalar_t__ PG0_CNTR0 ; 
 scalar_t__ PG0_CNTR1 ; 
 scalar_t__ PG0_CNTR2 ; 

VOID NICUpdateCounters(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Updates counters
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    UCHAR Tmp;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    NdisRawReadPortUchar(Adapter->IOBase + PG0_CNTR0, &Tmp);
    Adapter->FrameAlignmentErrors += Tmp;

    NdisRawReadPortUchar(Adapter->IOBase + PG0_CNTR1, &Tmp);
    Adapter->CrcErrors += Tmp;

    NdisRawReadPortUchar(Adapter->IOBase + PG0_CNTR2, &Tmp);
    Adapter->MissedPackets += Tmp;
}