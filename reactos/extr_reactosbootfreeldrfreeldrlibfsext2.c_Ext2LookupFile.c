#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UINT32 ;
struct TYPE_14__ {scalar_t__ inode; } ;
struct TYPE_13__ {int mode; scalar_t__ size; } ;
struct TYPE_12__ {int /*<<< orphan*/  Inode; scalar_t__ FileSize; scalar_t__ FilePointer; int /*<<< orphan*/ * FileBlockList; int /*<<< orphan*/  DriveNumber; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PEXT2_FILE_INFO ;
typedef  char* PCSTR ;
typedef  TYPE_2__ EXT2_INODE ;
typedef  int /*<<< orphan*/  EXT2_FILE_INFO ;
typedef  TYPE_3__ EXT2_DIR_ENTRY ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ EXT2_ROOT_INO ; 
 int EXT2_S_IFLNK ; 
 int EXT2_S_IFMT ; 
 int EXT2_S_IFREG ; 
 int /*<<< orphan*/  Ext2DriveNumber ; 
 scalar_t__ Ext2GetInodeFileSize (TYPE_2__*) ; 
 int /*<<< orphan*/ * Ext2ReadBlockPointerList (TYPE_2__*) ; 
 int /*<<< orphan*/  Ext2ReadDirectory (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Ext2ReadInode (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  Ext2SearchDirectoryBufferForFile (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAST_SYMLINK_MAX_NAME_SIZE ; 
 int /*<<< orphan*/  FileSystemError (char*) ; 
 int /*<<< orphan*/  FrLdrTempFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsGetFirstNameFromPath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FsGetNumPathParts (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TAG_EXT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2LookupFile(PCSTR FileName, PEXT2_FILE_INFO Ext2FileInfoPointer)
{
    UINT32        i;
    ULONG        NumberOfPathParts;
    CHAR        PathPart[261];
    PVOID        DirectoryBuffer;
    ULONG        DirectoryInode = EXT2_ROOT_INO;
    EXT2_INODE    InodeData;
    EXT2_DIR_ENTRY    DirectoryEntry;

    TRACE("Ext2LookupFile() FileName = %s\n", FileName);

    RtlZeroMemory(Ext2FileInfoPointer, sizeof(EXT2_FILE_INFO));

    //
    // Figure out how many sub-directories we are nested in
    //
    NumberOfPathParts = FsGetNumPathParts(FileName);

    //
    // Loop once for each part
    //
    for (i=0; i<NumberOfPathParts; i++)
    {
        //
        // Get first path part
        //
        FsGetFirstNameFromPath(PathPart, FileName);

        //
        // Advance to the next part of the path
        //
        for (; (*FileName != '\\') && (*FileName != '/') && (*FileName != '\0'); FileName++)
        {
        }
        FileName++;

        //
        // Buffer the directory contents
        //
        if (!Ext2ReadDirectory(DirectoryInode, &DirectoryBuffer, &InodeData))
        {
            return FALSE;
        }

        //
        // Search for file name in directory
        //
        if (!Ext2SearchDirectoryBufferForFile(DirectoryBuffer, (ULONG)Ext2GetInodeFileSize(&InodeData), PathPart, &DirectoryEntry))
        {
            FrLdrTempFree(DirectoryBuffer, TAG_EXT_BUFFER);
            return FALSE;
        }

        FrLdrTempFree(DirectoryBuffer, TAG_EXT_BUFFER);

        DirectoryInode = DirectoryEntry.inode;
    }

    if (!Ext2ReadInode(DirectoryInode, &InodeData))
    {
        return FALSE;
    }

    if (((InodeData.mode & EXT2_S_IFMT) != EXT2_S_IFREG) &&
        ((InodeData.mode & EXT2_S_IFMT) != EXT2_S_IFLNK))
    {
        FileSystemError("Inode is not a regular file or symbolic link.");
        return FALSE;
    }

    // Set the drive number
    Ext2FileInfoPointer->DriveNumber = Ext2DriveNumber;

    // If it's a regular file or a regular symbolic link
    // then get the block pointer list otherwise it must
    // be a fast symbolic link which doesn't have a block list
    if (((InodeData.mode & EXT2_S_IFMT) == EXT2_S_IFREG) ||
        ((InodeData.mode & EXT2_S_IFMT) == EXT2_S_IFLNK && InodeData.size > FAST_SYMLINK_MAX_NAME_SIZE))
    {
        Ext2FileInfoPointer->FileBlockList = Ext2ReadBlockPointerList(&InodeData);

        if (Ext2FileInfoPointer->FileBlockList == NULL)
        {
            return FALSE;
        }
    }
    else
    {
        Ext2FileInfoPointer->FileBlockList = NULL;
    }

    Ext2FileInfoPointer->FilePointer = 0;
    Ext2FileInfoPointer->FileSize = Ext2GetInodeFileSize(&InodeData);
    RtlCopyMemory(&Ext2FileInfoPointer->Inode, &InodeData, sizeof(EXT2_INODE));

    return TRUE;
}