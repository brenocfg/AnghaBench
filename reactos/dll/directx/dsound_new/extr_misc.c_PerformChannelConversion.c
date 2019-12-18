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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 

VOID
PerformChannelConversion(
    PUCHAR Buffer,
    ULONG BufferLength,
    PULONG BytesRead,
    ULONG OldChannels,
    ULONG NewChannels,
    ULONG BitsPerSample,
    PUCHAR Result,
    ULONG ResultLength,
    PULONG BytesWritten)
{
    DWORD NewIndex, OldIndex;
    DWORD NewLength, Skip;

    if (NewChannels > OldChannels)
    {
        UNIMPLEMENTED;
        ASSERT(0);
    }

    /* setup index */
    NewIndex = 0;
    OldIndex = 0;

    /* calculate offsets */
    NewLength = NewChannels * (BitsPerSample/8);
    Skip = OldChannels * (BitsPerSample/8);

    do
    {
        if (NewIndex + NewLength>= ResultLength)
        {
            NewIndex = ResultLength;
            break;
        }

        if (OldIndex + Skip >= BufferLength)
        {
            OldIndex = BufferLength;
            break;
        }

        /* copy first channel */
        RtlMoveMemory(&Result[NewIndex], &Buffer[OldIndex], NewLength);

        /* skip other channels */
        OldIndex += Skip;

        /* increment offset */
        NewIndex += NewLength;

    }while(TRUE);

    *BytesRead = OldIndex;
    *BytesWritten = NewIndex;
}