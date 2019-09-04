#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  size_t ULONG ;
struct TYPE_4__ {int mode; size_t symlink; } ;
struct TYPE_5__ {size_t* FileBlockList; scalar_t__ FileSize; int FilePointer; TYPE_1__ Inode; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_2__* PEXT2_FILE_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int EXT2_S_IFLNK ; 
 int EXT2_S_IFMT ; 
 int Ext2BlockSizeInBytes ; 
 int /*<<< orphan*/  Ext2ReadBlock (size_t,scalar_t__) ; 
 int /*<<< orphan*/  Ext2ReadPartialBlock (size_t,size_t,size_t,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAST_SYMLINK_MAX_NAME_SIZE ; 
 int /*<<< orphan*/  FileSystemError (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2ReadFileBig(PEXT2_FILE_INFO Ext2FileInfo, ULONGLONG BytesToRead, ULONGLONG* BytesRead, PVOID Buffer)
{
    ULONG                BlockNumber;
    ULONG                BlockNumberIndex;
    ULONG                OffsetInBlock;
    ULONG                LengthInBlock;
    ULONG                NumberOfBlocks;

    TRACE("Ext2ReadFileBig() BytesToRead = %d Buffer = 0x%x\n", (ULONG)BytesToRead, Buffer);

    if (BytesRead != NULL)
    {
        *BytesRead = 0;
    }

    // Make sure we have the block pointer list if we need it
    if (Ext2FileInfo->FileBlockList == NULL)
    {
        // Block pointer list is NULL
        // so this better be a fast symbolic link or else
        if (((Ext2FileInfo->Inode.mode & EXT2_S_IFMT) != EXT2_S_IFLNK) ||
            (Ext2FileInfo->FileSize > FAST_SYMLINK_MAX_NAME_SIZE))
        {
            FileSystemError("Block pointer list is NULL and file is not a fast symbolic link.");
            return FALSE;
        }
    }

    //
    // If they are trying to read past the
    // end of the file then return success
    // with BytesRead == 0
    //
    if (Ext2FileInfo->FilePointer >= Ext2FileInfo->FileSize)
    {
        return TRUE;
    }

    //
    // If they are trying to read more than there is to read
    // then adjust the amount to read
    //
    if ((Ext2FileInfo->FilePointer + BytesToRead) > Ext2FileInfo->FileSize)
    {
        BytesToRead = (Ext2FileInfo->FileSize - Ext2FileInfo->FilePointer);
    }

    // Check if this is a fast symbolic link
    // if so then the read is easy
    if (((Ext2FileInfo->Inode.mode & EXT2_S_IFMT) == EXT2_S_IFLNK) &&
        (Ext2FileInfo->FileSize <= FAST_SYMLINK_MAX_NAME_SIZE))
    {
        TRACE("Reading fast symbolic link data\n");

        // Copy the data from the link
        RtlCopyMemory(Buffer, (PVOID)((ULONG_PTR)Ext2FileInfo->FilePointer + Ext2FileInfo->Inode.symlink), (ULONG)BytesToRead);

        if (BytesRead != NULL)
        {
            *BytesRead = BytesToRead;
        }

        return TRUE;
    }

    //
    // Ok, now we have to perform at most 3 calculations
    // I'll draw you a picture (using nifty ASCII art):
    //
    // CurrentFilePointer -+
    //                     |
    //    +----------------+
    //    |
    // +-----------+-----------+-----------+-----------+
    // | Block 1   | Block 2   | Block 3   | Block 4   |
    // +-----------+-----------+-----------+-----------+
    //    |                                    |
    //    +---------------+--------------------+
    //                    |
    // BytesToRead -------+
    //
    // 1 - The first calculation (and read) will align
    //     the file pointer with the next block.
    //     boundary (if we are supposed to read that much)
    // 2 - The next calculation (and read) will read
    //     in all the full blocks that the requested
    //     amount of data would cover (in this case
    //     blocks 2 & 3).
    // 3 - The last calculation (and read) would read
    //     in the remainder of the data requested out of
    //     the last block.
    //

    //
    // Only do the first read if we
    // aren't aligned on a block boundary
    //
    if (Ext2FileInfo->FilePointer % Ext2BlockSizeInBytes)
    {
        //
        // Do the math for our first read
        //
        BlockNumberIndex = (ULONG)(Ext2FileInfo->FilePointer / Ext2BlockSizeInBytes);
        BlockNumber = Ext2FileInfo->FileBlockList[BlockNumberIndex];
        OffsetInBlock = (Ext2FileInfo->FilePointer % Ext2BlockSizeInBytes);
        LengthInBlock = (ULONG)((BytesToRead > (Ext2BlockSizeInBytes - OffsetInBlock)) ? (Ext2BlockSizeInBytes - OffsetInBlock) : BytesToRead);

        //
        // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
        //
        if (!Ext2ReadPartialBlock(BlockNumber, OffsetInBlock, LengthInBlock, Buffer))
        {
            return FALSE;
        }
        if (BytesRead != NULL)
        {
            *BytesRead += LengthInBlock;
        }
        BytesToRead -= LengthInBlock;
        Ext2FileInfo->FilePointer += LengthInBlock;
        Buffer = (PVOID)((ULONG_PTR)Buffer + LengthInBlock);
    }

    //
    // Do the math for our second read (if any data left)
    //
    if (BytesToRead > 0)
    {
        //
        // Determine how many full clusters we need to read
        //
        NumberOfBlocks = (ULONG)(BytesToRead / Ext2BlockSizeInBytes);

        while (NumberOfBlocks > 0)
        {
            BlockNumberIndex = (ULONG)(Ext2FileInfo->FilePointer / Ext2BlockSizeInBytes);
            BlockNumber = Ext2FileInfo->FileBlockList[BlockNumberIndex];

            //
            // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
            //
            if (!Ext2ReadBlock(BlockNumber, Buffer))
            {
                return FALSE;
            }
            if (BytesRead != NULL)
            {
                *BytesRead += Ext2BlockSizeInBytes;
            }
            BytesToRead -= Ext2BlockSizeInBytes;
            Ext2FileInfo->FilePointer += Ext2BlockSizeInBytes;
            Buffer = (PVOID)((ULONG_PTR)Buffer + Ext2BlockSizeInBytes);
            NumberOfBlocks--;
        }
    }

    //
    // Do the math for our third read (if any data left)
    //
    if (BytesToRead > 0)
    {
        BlockNumberIndex = (ULONG)(Ext2FileInfo->FilePointer / Ext2BlockSizeInBytes);
        BlockNumber = Ext2FileInfo->FileBlockList[BlockNumberIndex];

        //
        // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
        //
        if (!Ext2ReadPartialBlock(BlockNumber, 0, (ULONG)BytesToRead, Buffer))
        {
            return FALSE;
        }
        if (BytesRead != NULL)
        {
            *BytesRead += BytesToRead;
        }
        Ext2FileInfo->FilePointer += BytesToRead;
        BytesToRead -= BytesToRead;
        Buffer = (PVOID)((ULONG_PTR)Buffer + (ULONG_PTR)BytesToRead);
    }

    return TRUE;
}