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
typedef  int USHORT ;
typedef  int ULONG_PTR ;
typedef  int UCHAR ;
struct TYPE_3__ {scalar_t__ IOBase; scalar_t__ WordMode; } ;
typedef  int /*<<< orphan*/  PUSHORT ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_RD0 ; 
 int CR_RD1 ; 
 int CR_RD2 ; 
 int CR_STA ; 
 int ISR_RDC ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NIC_DATA ; 
 int /*<<< orphan*/  NdisRawReadPortUchar (scalar_t__,int*) ; 
 int /*<<< orphan*/  NdisRawReadPortUshort (scalar_t__,int*) ; 
 int /*<<< orphan*/  NdisRawWritePortBufferUchar (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NdisRawWritePortBufferUshort (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 int /*<<< orphan*/  NdisStallExecution (int) ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG0_ISR ; 
 scalar_t__ PG0_RBCR0 ; 
 scalar_t__ PG0_RBCR1 ; 
 scalar_t__ PG0_RSAR0 ; 
 scalar_t__ PG0_RSAR1 ; 

VOID NICWriteDataAlign(
    PNIC_ADAPTER Adapter,
    ULONG_PTR Target,
    PUSHORT Source,
    USHORT Length)
/*
 * FUNCTION: Copies data from a buffer into the NIC's RAM
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 *     Target  = Offset into NIC's RAM (must be an even number)
 *     Source  = Pointer to buffer to copy data from (in host memory)
 *     Length  = Number of bytes to copy from the buffer (must be an even number)
 */
{
    UCHAR Tmp;
    USHORT Count;

    /* Select page 0 and start the NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD2 | CR_PAGE0);

    /* Handle read-before-write bug */

    /* Initialize RSAR0 and RSAR1 - Remote Start Address Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR0, (UCHAR)(Target & 0xFF));
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR1, (UCHAR)(Target >> 8));

    /* Initialize RBCR0 and RBCR1 - Remote Byte Count Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR0, 0x02);
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR1, 0x00);

    /* Read and start the NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD0 | CR_PAGE0);

    /* Read data */
    NdisRawReadPortUshort(Adapter->IOBase + NIC_DATA, &Count);

    /* Wait for remote DMA to complete, but timeout after some time */
    for (Count = 0; Count < 0xFFFF; Count++) {
        NdisRawReadPortUchar(Adapter->IOBase + PG0_ISR, &Tmp);
        if (Tmp & ISR_RDC)
            break;

        NdisStallExecution(4);
    }

#if DBG
    if (Count == 0xFFFF)
        NDIS_DbgPrint(MIN_TRACE, ("Remote DMA did not complete.\n"));
#endif

    /* Clear remote DMA bit in ISR - Interrupt Status Register */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_ISR, ISR_RDC);


    /* Now output some data */
    Count = Length;

    /* Initialize RSAR0 and RSAR1 - Remote Start Address Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR0, (UCHAR)(Target & 0xFF));
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR1, (UCHAR)(Target >> 8));

    /* Initialize RBCR0 and RBCR1 - Remote Byte Count Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR0, (UCHAR)(Count & 0xFF));
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR1, (UCHAR)(Count >> 8));

    /* Write and start the NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD1 | CR_PAGE0);

    if (Adapter->WordMode)
        NdisRawWritePortBufferUshort(Adapter->IOBase + NIC_DATA, Source, Count >> 1);
    else
        NdisRawWritePortBufferUchar(Adapter->IOBase + NIC_DATA, Source, Count);

    /* Wait for remote DMA to complete, but timeout after some time */
    for (Count = 0; Count < 0xFFFF; Count++) {
        NdisRawReadPortUchar(Adapter->IOBase + PG0_ISR, &Tmp);
        if (Tmp & ISR_RDC)
            break;

        NdisStallExecution(4);
    }

#if DBG
    if (Count == 0xFFFF)
        NDIS_DbgPrint(MIN_TRACE, ("Remote DMA did not complete.\n"));
#endif

    /* Clear remote DMA bit in ISR - Interrupt Status Register */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_ISR, ISR_RDC);
}