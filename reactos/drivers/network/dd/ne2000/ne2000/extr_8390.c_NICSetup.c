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
struct TYPE_5__ {int NextPacket; int PageStart; int PageStop; int InterruptMask; int CurrentPage; void* TransmitError; void* ReceiveError; void* BufferOverflow; scalar_t__ IOBase; scalar_t__ WordMode; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_PAGE1 ; 
 int CR_RD2 ; 
 int CR_STA ; 
 int CR_STP ; 
 int DCR_FT10 ; 
 int DCR_LS ; 
 int DCR_WTS ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NICSetMulticastAddressMask (TYPE_1__*) ; 
 int /*<<< orphan*/  NICSetPhysicalAddress (TYPE_1__*) ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 scalar_t__ PG0_BNRY ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG0_DCR ; 
 scalar_t__ PG0_IMR ; 
 scalar_t__ PG0_ISR ; 
 scalar_t__ PG0_PSTART ; 
 scalar_t__ PG0_PSTOP ; 
 scalar_t__ PG0_RBCR0 ; 
 scalar_t__ PG0_RBCR1 ; 
 scalar_t__ PG0_RCR ; 
 scalar_t__ PG0_TCR ; 
 scalar_t__ PG1_CURR ; 
 int RCR_MON ; 
 int TCR_LOOP ; 

NDIS_STATUS NICSetup(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Sets up a NIC
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * RETURNS:
 *     Status of operation
 * NOTES:
 *     The NIC is put into loopback mode
 */
{
    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    if (Adapter->WordMode ) {
        /* Initialize DCR - Data Configuration Register (word mode/4 words FIFO) */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_DCR, DCR_WTS | DCR_LS | DCR_FT10);
    } else {
        /* Initialize DCR - Data Configuration Register (byte mode/8 bytes FIFO) */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_DCR, DCR_LS | DCR_FT10);
    }

    /* Clear RBCR0 and RBCR1 - Remote Byte Count Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR0, 0x00);
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR1, 0x00);

    /* Initialize RCR - Receive Configuration Register (monitor mode) */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RCR, RCR_MON);

    /* Enter loopback mode (internal NIC module loopback) */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_TCR, TCR_LOOP);

    /* Set boundary page */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_BNRY, Adapter->NextPacket);

    /* Set start page */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_PSTART, Adapter->PageStart);

    /* Set stop page */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_PSTOP, Adapter->PageStop);

    /* Program our address on the NIC */
    NICSetPhysicalAddress(Adapter);

    /* Program the multicast address mask on the NIC */
    NICSetMulticastAddressMask(Adapter);

    /* Select page 1 and stop NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STP | CR_RD2 | CR_PAGE1);

    /* Initialize current page register */
    NdisRawWritePortUchar(Adapter->IOBase + PG1_CURR, Adapter->PageStart + 1);

    /* Select page 0 and stop NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STP | CR_RD2 | CR_PAGE0);

    /* Clear ISR - Interrupt Status Register */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_ISR, 0xFF);

    /* Initialize IMR - Interrupt Mask Register */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_IMR, Adapter->InterruptMask);

    /* Select page 0 and start NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD2 | CR_PAGE0);

    Adapter->CurrentPage            = Adapter->PageStart + 1;
    Adapter->NextPacket             = Adapter->PageStart + 1;
    Adapter->BufferOverflow         = FALSE;
    Adapter->ReceiveError           = FALSE;
    Adapter->TransmitError          = FALSE;

    NDIS_DbgPrint(MAX_TRACE, ("Leaving.\n"));

    return NDIS_STATUS_SUCCESS;
}