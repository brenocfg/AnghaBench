#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_8__ {int InterruptStatus; scalar_t__ NextPacket; scalar_t__ CurrentPage; int TXCurrent; int /*<<< orphan*/  MiniportAdapterHandle; void* DoneIndicating; void* TransmitPending; void* ReceiveError; void* BufferOverflow; scalar_t__ IOBase; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_RD2 ; 
 int CR_STA ; 
 int CR_STP ; 
 void* FALSE ; 
 int ISR_PTX ; 
 int ISR_RST ; 
 int ISR_TXE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NICGetCurrentPage (TYPE_1__*) ; 
 int /*<<< orphan*/  NICReadPacket (TYPE_1__*) ; 
 int /*<<< orphan*/  NICSetBoundaryPage (TYPE_1__*) ; 
 int /*<<< orphan*/  NICStart (TYPE_1__*) ; 
 int /*<<< orphan*/  NICStartTransmit (TYPE_1__*) ; 
 int /*<<< orphan*/  NdisMEthIndicateReceiveComplete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisRawReadPortUchar (scalar_t__,int*) ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 int /*<<< orphan*/  NdisStallExecution (int) ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG0_ISR ; 
 scalar_t__ PG0_RBCR0 ; 
 scalar_t__ PG0_RBCR1 ; 
 scalar_t__ PG0_TCR ; 
 int TCR_LOOP ; 
 void* TRUE ; 

__attribute__((used)) static VOID HandleReceive(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Handles reception of a packet
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * NOTES:
 *     Buffer overflows are also handled here
 */
{
    UINT i;
    UCHAR Tmp;
    UINT PacketCount;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    Adapter->DoneIndicating = FALSE;
    PacketCount = 0;

    NICGetCurrentPage(Adapter);

    if (Adapter->BufferOverflow) {

        NDIS_DbgPrint(MID_TRACE, ("Receive ring overflow.\n"));

        /* Select page 0 and stop the NIC */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STP | CR_RD2 | CR_PAGE0);

        /* Clear RBCR0,RBCR1 - Remote Byte Count Registers */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR0, 0x00);
        NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR1, 0x00);

        /* Wait for ISR_RST to be set, but timeout after 2ms */
        for (i = 0; i < 4; i++) {
            NdisRawReadPortUchar(Adapter->IOBase + PG0_ISR, &Tmp);
            if (Tmp & ISR_RST)
                break;

            NdisStallExecution(500);
        }

#if DBG
        if (i == 4)
            NDIS_DbgPrint(MIN_TRACE, ("NIC was not reset after 2ms.\n"));
#endif

        if ((Adapter->InterruptStatus & (ISR_PTX | ISR_TXE)) == 0) {
            /* We may need to restart the transmitter */
            Adapter->TransmitPending = TRUE;
        }

        /* Initialize TCR - Transmit Configuration Register to loopback mode 1 */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_TCR, TCR_LOOP);

        /* Start NIC */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD2);

        NICStart(Adapter);

        Adapter->BufferOverflow = FALSE;
    }

    if (Adapter->ReceiveError) {
        NDIS_DbgPrint(MID_TRACE, ("Receive error.\n"));

        /* Skip this packet */
        Adapter->NextPacket = Adapter->CurrentPage;
        NICSetBoundaryPage(Adapter);

        Adapter->ReceiveError = FALSE;
    }

    for (;;) {
        NICGetCurrentPage(Adapter);

        NDIS_DbgPrint(MID_TRACE, ("Current page (0x%X)  NextPacket (0x%X).\n",
            Adapter->CurrentPage,
            Adapter->NextPacket));

        if (Adapter->CurrentPage == Adapter->NextPacket) {
            NDIS_DbgPrint(MID_TRACE, ("No more packets.\n"));
            break;
        } else {
            NDIS_DbgPrint(MID_TRACE, ("Got a packet in the receive ring.\n"));

	    NDIS_DbgPrint(MAX_TRACE,("Adapter->MiniportAdapterHandle: %x\n",
				     Adapter->MiniportAdapterHandle));
            /* Read packet from receive buffer ring */
            NICReadPacket(Adapter);

            Adapter->DoneIndicating = TRUE;

            PacketCount++;
            if (PacketCount == 10) {
                /* Don't starve transmit interrupts */
                break;
            }
        }
    }

    if ((Adapter->TransmitPending) && (Adapter->TXCurrent != -1)) {
        NDIS_DbgPrint(MID_TRACE, ("Retransmitting current packet at (%d).\n", Adapter->TXCurrent));
        /* Retransmit packet */
        NICStartTransmit(Adapter);
        Adapter->TransmitPending = FALSE;
    }

    if (Adapter->DoneIndicating)
        NdisMEthIndicateReceiveComplete(Adapter->MiniportAdapterHandle);
}