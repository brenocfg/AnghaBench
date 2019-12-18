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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CopyBufferChainToBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NdisGetFirstBufferFromPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

UINT CopyPacketToBuffer(
    PUCHAR DstData,
    PNDIS_PACKET SrcPacket,
    UINT SrcOffset,
    UINT Length)
/*
 * FUNCTION: Copies data from an NDIS packet to a buffer
 * ARGUMENTS:
 *     DstData   = Pointer to destination buffer
 *     SrcPacket = Pointer to source NDIS packet
 *     SrcOffset = Source start offset
 *     Length    = Number of bytes to copy
 * RETURNS:
 *     Number of bytes copied to destination buffer
 * NOTES:
 *     The number of bytes copied may be limited by the source
 *     buffer size
 */
{
    PNDIS_BUFFER FirstBuffer;
    PVOID Address;
    UINT FirstLength;
    UINT TotalLength;

    NDIS_DbgPrint(MAX_TRACE, ("DstData (0x%X)  SrcPacket (0x%X)  SrcOffset (0x%X)  Length (%d)\n", DstData, SrcPacket, SrcOffset, Length));

    NdisGetFirstBufferFromPacket(SrcPacket,
                                 &FirstBuffer,
                                 &Address,
                                 &FirstLength,
                                 &TotalLength);

    return CopyBufferChainToBuffer(DstData, FirstBuffer, SrcOffset, Length);
}