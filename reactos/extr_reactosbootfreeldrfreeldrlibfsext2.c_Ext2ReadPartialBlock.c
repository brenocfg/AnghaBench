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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2BlockSizeInBytes ; 
 int /*<<< orphan*/  Ext2ReadBlock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FrLdrTempAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_EXT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

BOOLEAN Ext2ReadPartialBlock(ULONG BlockNumber, ULONG StartingOffset, ULONG Length, PVOID Buffer)
{
    PVOID TempBuffer;

    TRACE("Ext2ReadPartialBlock() BlockNumber = %d StartingOffset = %d Length = %d Buffer = 0x%x\n", BlockNumber, StartingOffset, Length, Buffer);

    TempBuffer = FrLdrTempAlloc(Ext2BlockSizeInBytes, TAG_EXT_BUFFER);

    if (!Ext2ReadBlock(BlockNumber, TempBuffer))
    {
        return FALSE;
    }

    memcpy(Buffer, ((PUCHAR)TempBuffer + StartingOffset), Length);

    FrLdrTempFree(TempBuffer, TAG_EXT_BUFFER);

    return TRUE;
}