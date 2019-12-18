#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int NextPacket; int PacketLength; int /*<<< orphan*/  Status; } ;
struct TYPE_8__ {int PacketOffset; int NextPacket; int CurrentPage; TYPE_1__ PacketHeader; int /*<<< orphan*/  MiniportAdapterHandle; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  PACKET_HEADER ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NICIndicatePacket (TYPE_2__*) ; 
 int /*<<< orphan*/  NICReadData (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NICSetBoundaryPage (TYPE_2__*) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static VOID NICReadPacket(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Reads a full packet from the receive buffer ring
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    BOOLEAN SkipPacket = FALSE;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* Get the header of the next packet in the receive ring */
    Adapter->PacketOffset = Adapter->NextPacket << 8;
    NICReadData(Adapter,
                (PUCHAR)&Adapter->PacketHeader,
                Adapter->PacketOffset,
                sizeof(PACKET_HEADER));

    NDIS_DbgPrint(MAX_TRACE, ("HEADER: (Status)       (0x%X)\n", Adapter->PacketHeader.Status));
    NDIS_DbgPrint(MAX_TRACE, ("HEADER: (NextPacket)   (0x%X)\n", Adapter->PacketHeader.NextPacket));
    NDIS_DbgPrint(MAX_TRACE, ("HEADER: (PacketLength) (0x%X)\n", Adapter->PacketHeader.PacketLength));

    if (Adapter->PacketHeader.PacketLength < 64  ||
        Adapter->PacketHeader.PacketLength > 1518) {	/* XXX I don't think the CRC will show up... should be 1514 */
        NDIS_DbgPrint(MAX_TRACE, ("Bogus packet size (%d).\n",
            Adapter->PacketHeader.PacketLength));
        SkipPacket = TRUE;
    }

    if (SkipPacket) {
        /* Skip packet */
        Adapter->NextPacket = Adapter->CurrentPage;
    } else {
	NDIS_DbgPrint(MAX_TRACE,("Adapter->MiniportAdapterHandle: %x\n",
				 Adapter->MiniportAdapterHandle));
        NICIndicatePacket(Adapter);

        /* Go to the next free buffer in receive ring */
        Adapter->NextPacket = Adapter->PacketHeader.NextPacket;
    }

    /* Update boundary page */
    NICSetBoundaryPage(Adapter);
}