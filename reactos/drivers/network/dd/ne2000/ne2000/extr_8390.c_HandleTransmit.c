#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_5__ {int* TXSize; size_t TXCurrent; int TXFree; int TXCount; scalar_t__ TXQueueTail; scalar_t__ TransmitError; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int DRIVER_BLOCK_SIZE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NICPrepareForTransmit (TYPE_1__*) ; 
 int /*<<< orphan*/  NICStartTransmit (TYPE_1__*) ; 

__attribute__((used)) static VOID HandleTransmit(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Handles transmission of a packet
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    UINT Length;
    UINT BufferCount;

//    PIP_PACKET pIPPacket;
//    pIPPacket = (PIP_PACKET)
//    DisplayIPPacket(pIPPacket);

    if (Adapter->TransmitError) {
        /* FIXME: Retransmit now or let upper layer protocols handle retransmit? */
        Adapter->TransmitError = FALSE;
    }

    /* Free transmit buffers */
    Length      = Adapter->TXSize[Adapter->TXCurrent];
    BufferCount = (Length + DRIVER_BLOCK_SIZE - 1) / DRIVER_BLOCK_SIZE;

    NDIS_DbgPrint(MID_TRACE, ("Freeing (%d) buffers at (%d).\n",
        BufferCount,
        Adapter->TXCurrent));

    Adapter->TXFree += BufferCount;
    Adapter->TXSize[Adapter->TXCurrent] = 0;
    Adapter->TXCurrent = (Adapter->TXCurrent + BufferCount) % Adapter->TXCount;

    if (Adapter->TXSize[Adapter->TXCurrent] == 0) {
        NDIS_DbgPrint(MID_TRACE, ("No more packets in transmit buffer.\n"));

        Adapter->TXCurrent = -1;
    }

    if (Adapter->TXQueueTail) {
        if (NICPrepareForTransmit(Adapter))
            NICStartTransmit(Adapter);
    }
}