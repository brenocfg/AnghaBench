#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ total_blocks; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2BlockSizeInBytes ; 
 int Ext2BlockSizeInSectors ; 
 int /*<<< orphan*/  Ext2DriveNumber ; 
 int /*<<< orphan*/  Ext2ReadVolumeSectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* Ext2SuperBlock ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileSystemError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

BOOLEAN Ext2ReadBlock(ULONG BlockNumber, PVOID Buffer)
{
    CHAR    ErrorString[80];

    TRACE("Ext2ReadBlock() BlockNumber = %d Buffer = 0x%x\n", BlockNumber, Buffer);

    // Make sure its a valid block
    if (BlockNumber > Ext2SuperBlock->total_blocks)
    {
        sprintf(ErrorString, "Error reading block %d - block out of range.", (int) BlockNumber);
        FileSystemError(ErrorString);
        return FALSE;
    }

    // Check to see if this is a sparse block
    if (BlockNumber == 0)
    {
        TRACE("Block is part of a sparse file. Zeroing input buffer.\n");

        RtlZeroMemory(Buffer, Ext2BlockSizeInBytes);

        return TRUE;
    }

    return Ext2ReadVolumeSectors(Ext2DriveNumber, (ULONGLONG)BlockNumber * Ext2BlockSizeInSectors, Ext2BlockSizeInSectors, Buffer);
}