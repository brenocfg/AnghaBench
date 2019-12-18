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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ ByteCount; } ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  TYPE_1__* PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  NdisQueryPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 

UINT ResizePacket(
    PNDIS_PACKET Packet,
    UINT Size)
/*
 * FUNCTION: Resizes an NDIS packet
 * ARGUMENTS:
 *     Packet = Pointer to packet
 *     Size   = Number of bytes in first buffer
 * RETURNS:
 *     Previous size of first buffer
 */
{
    PNDIS_BUFFER NdisBuffer;
    UINT OldSize;

    NdisQueryPacket(Packet, NULL, NULL, &NdisBuffer, NULL);

    OldSize = NdisBuffer->ByteCount;

    if (Size != OldSize)
        NdisBuffer->ByteCount = Size;

    return OldSize;
}