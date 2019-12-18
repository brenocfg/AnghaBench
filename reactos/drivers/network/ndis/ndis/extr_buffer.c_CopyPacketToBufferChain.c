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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NdisGetFirstBufferFromPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int SkipToOffset (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 

UINT CopyPacketToBufferChain(
    PNDIS_BUFFER DstBuffer,
    UINT DstOffset,
    PNDIS_PACKET SrcPacket,
    UINT SrcOffset,
    UINT Length)
/*
 * FUNCTION: Copies data from an NDIS packet to an NDIS buffer chain
 * ARGUMENTS:
 *     DstBuffer = Pointer to destination NDIS buffer
 *     DstOffset = Destination start offset
 *     SrcPacket = Pointer to source NDIS packet
 *     SrcOffset = Source start offset
 *     Length    = Number of bytes to copy
 * RETURNS:
 *     Number of bytes copied to destination buffer
 * NOTES:
 *     The number of bytes copied may be limited by the source and
 *     destination buffer sizes
 */
{
    PNDIS_BUFFER SrcBuffer;
    PUCHAR DstData, SrcData;
    UINT DstSize, SrcSize;
    UINT Count, Total;

    NDIS_DbgPrint(MAX_TRACE, ("DstBuffer (0x%X)  DstOffset (0x%X)  SrcPacket (0x%X)  SrcOffset (0x%X)  Length (%d)\n", DstBuffer, DstOffset, SrcPacket, SrcOffset, Length));

    /* Skip DstOffset bytes in the destination buffer chain */
    NdisQueryBuffer(DstBuffer, (PVOID)&DstData, &DstSize);
    if (SkipToOffset(DstBuffer, DstOffset, &DstData, &DstSize) == 0xFFFFFFFF)
        return 0;
    /* Skip SrcOffset bytes in the source packet */
    NdisGetFirstBufferFromPacket(SrcPacket, &SrcBuffer, (PVOID*)&SrcData, &SrcSize, &Total);
    if (SkipToOffset(SrcBuffer, SrcOffset, &SrcData, &SrcSize) == 0xFFFFFFFF)
        return 0;
    /* Copy the data */
    for (Total = 0;;) {
        /* Find out how many bytes we can copy at one time */
        if (Length < SrcSize)
            Count = Length;
        else
            Count = SrcSize;
        if (DstSize < Count)
            Count = DstSize;

        RtlCopyMemory((PVOID)DstData, (PVOID)SrcData, Count);

        Total  += Count;
        Length -= Count;
        if (Length == 0)
            break;

        DstSize -= Count;
        if (DstSize == 0) {
            /* No more bytes in destination buffer. Proceed to
               the next buffer in the destination buffer chain */
            NdisGetNextBuffer(DstBuffer, &DstBuffer);
            if (!DstBuffer)
                break;

            NdisQueryBuffer(DstBuffer, (PVOID)&DstData, &DstSize);
        }

        SrcSize -= Count;
        if (SrcSize == 0) {
            /* No more bytes in source buffer. Proceed to
               the next buffer in the source buffer chain */
            NdisGetNextBuffer(SrcBuffer, &SrcBuffer);
            if (!SrcBuffer)
                break;

            NdisQueryBuffer(SrcBuffer, (PVOID)&SrcData, &SrcSize);
        }
    }

    return Total;
}