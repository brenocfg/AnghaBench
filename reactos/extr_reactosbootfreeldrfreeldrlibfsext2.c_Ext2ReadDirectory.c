#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {int FileSize; int /*<<< orphan*/ * FileBlockList; scalar_t__ FilePointer; int /*<<< orphan*/  DriveNumber; } ;
struct TYPE_9__ {int mode; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PEXT2_INODE ;
typedef  int /*<<< orphan*/ * PEXT2_DIR_ENTRY ;
typedef  TYPE_2__ EXT2_FILE_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EXT2_S_IFDIR ; 
 int EXT2_S_IFMT ; 
 int /*<<< orphan*/  Ext2DriveNumber ; 
 int Ext2GetInodeFileSize (TYPE_1__*) ; 
 int /*<<< orphan*/ * Ext2ReadBlockPointerList (TYPE_1__*) ; 
 int /*<<< orphan*/  Ext2ReadFileBig (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2ReadInode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileSystemError (char*) ; 
 scalar_t__ FrLdrTempAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TAG_EXT_BLOCK_LIST ; 
 int /*<<< orphan*/  TAG_EXT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2ReadDirectory(ULONG Inode, PVOID* DirectoryBuffer, PEXT2_INODE InodePointer)
{
    EXT2_FILE_INFO    DirectoryFileInfo;

    TRACE("Ext2ReadDirectory() Inode = %d\n", Inode);

    // Read the directory inode
    if (!Ext2ReadInode(Inode, InodePointer))
    {
        return FALSE;
    }

    // Make sure it is a directory inode
    if ((InodePointer->mode & EXT2_S_IFMT) != EXT2_S_IFDIR)
    {
        FileSystemError("Inode is not a directory.");
        return FALSE;
    }

    // Fill in file info struct so we can call Ext2ReadFileBig()
    RtlZeroMemory(&DirectoryFileInfo, sizeof(EXT2_FILE_INFO));
    DirectoryFileInfo.DriveNumber = Ext2DriveNumber;
    DirectoryFileInfo.FileBlockList = Ext2ReadBlockPointerList(InodePointer);
    DirectoryFileInfo.FilePointer = 0;
    DirectoryFileInfo.FileSize = Ext2GetInodeFileSize(InodePointer);

    if (DirectoryFileInfo.FileBlockList == NULL)
    {
        return FALSE;
    }

    //
    // Now allocate the memory to hold the group descriptors
    //
    ASSERT(DirectoryFileInfo.FileSize <= 0xFFFFFFFF);
    *DirectoryBuffer = (PEXT2_DIR_ENTRY)FrLdrTempAlloc((ULONG)DirectoryFileInfo.FileSize, TAG_EXT_BUFFER);

    //
    // Make sure we got the memory
    //
    if (*DirectoryBuffer == NULL)
    {
        FrLdrTempFree(DirectoryFileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
        FileSystemError("Out of memory.");
        return FALSE;
    }

    // Now read the root directory data
    if (!Ext2ReadFileBig(&DirectoryFileInfo, DirectoryFileInfo.FileSize, NULL, *DirectoryBuffer))
    {
        FrLdrTempFree(*DirectoryBuffer, TAG_EXT_BUFFER);
        *DirectoryBuffer = NULL;
        FrLdrTempFree(DirectoryFileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
        return FALSE;
    }

    FrLdrTempFree(DirectoryFileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
    return TRUE;
}