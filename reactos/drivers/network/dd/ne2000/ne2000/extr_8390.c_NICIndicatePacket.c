#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_5__ {scalar_t__ PacketLength; } ;
struct TYPE_6__ {scalar_t__ LookaheadSize; int /*<<< orphan*/ * Lookahead; int /*<<< orphan*/  MiniportAdapterHandle; TYPE_1__ PacketHeader; scalar_t__ PacketOffset; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  PACKET_HEADER ;

/* Variables and functions */
 int DRIVER_HEADER_SIZE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NICReadData (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  NdisMEthIndicateReceive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int i ; 

__attribute__((used)) static VOID NICIndicatePacket(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Indicates a packet to the wrapper
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    UINT IndicateLength;

    IndicateLength = (Adapter->PacketHeader.PacketLength <
        (Adapter->LookaheadSize + DRIVER_HEADER_SIZE))?
        (Adapter->PacketHeader.PacketLength) :
        (Adapter->LookaheadSize + DRIVER_HEADER_SIZE);

    /* Fill the lookahead buffer */
    NICReadData(Adapter,
                (PUCHAR)&Adapter->Lookahead,
                Adapter->PacketOffset + sizeof(PACKET_HEADER),
                IndicateLength + DRIVER_HEADER_SIZE);

    NDIS_DbgPrint(MID_TRACE, ("Indicating (%d) bytes.\n", IndicateLength));
    NDIS_DbgPrint(MID_TRACE, ("ne2000!NICIndicatePacket: Indicating (%d) bytes.\n", IndicateLength));

#if 0
    NDIS_DbgPrint(MAX_TRACE, ("FRAME:\n"));
    for (i = 0; i < (IndicateLength + 7) / 8; i++) {
        NDIS_DbgPrint(MAX_TRACE, ("%02X %02X %02X %02X %02X %02X %02X %02X\n",
            Adapter->Lookahead[i*8+0],
            Adapter->Lookahead[i*8+1],
            Adapter->Lookahead[i*8+2],
            Adapter->Lookahead[i*8+3],
            Adapter->Lookahead[i*8+4],
            Adapter->Lookahead[i*8+5],
            Adapter->Lookahead[i*8+6],
            Adapter->Lookahead[i*8+7]));
    }
#endif

    if (IndicateLength >= DRIVER_HEADER_SIZE) {
	NDIS_DbgPrint(MAX_TRACE,("Adapter->MiniportAdapterHandle: %x\n",
				 Adapter->MiniportAdapterHandle));
        NdisMEthIndicateReceive(Adapter->MiniportAdapterHandle,
                                NULL,
                                (PVOID)&Adapter->Lookahead,
                                DRIVER_HEADER_SIZE,
                                (PVOID)&Adapter->Lookahead[DRIVER_HEADER_SIZE],
                                IndicateLength - DRIVER_HEADER_SIZE,
                                Adapter->PacketHeader.PacketLength - DRIVER_HEADER_SIZE);
    } else {
        NdisMEthIndicateReceive(Adapter->MiniportAdapterHandle,
                                NULL,
                                (PVOID)&Adapter->Lookahead,
                                IndicateLength,
                                NULL,
                                0,
                                0);
    }
}