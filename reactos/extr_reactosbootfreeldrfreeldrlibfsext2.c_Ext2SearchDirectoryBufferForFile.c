#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_6__ {scalar_t__ direntlen; scalar_t__ namelen; int /*<<< orphan*/ * name; int /*<<< orphan*/  filetype; int /*<<< orphan*/  inode; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PEXT2_DIR_ENTRY ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  EXT2_DIR_ENTRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT_FILESYSTEM ; 
 int /*<<< orphan*/  DbgDumpBuffer (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileSystemError (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _strnicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

BOOLEAN Ext2SearchDirectoryBufferForFile(PVOID DirectoryBuffer, ULONG DirectorySize, PCHAR FileName, PEXT2_DIR_ENTRY DirectoryEntry)
{
    ULONG        CurrentOffset;
    PEXT2_DIR_ENTRY    CurrentDirectoryEntry;

    TRACE("Ext2SearchDirectoryBufferForFile() DirectoryBuffer = 0x%x DirectorySize = %d FileName = %s\n", DirectoryBuffer, DirectorySize, FileName);

    for (CurrentOffset=0; CurrentOffset<DirectorySize; )
    {
        CurrentDirectoryEntry = (PEXT2_DIR_ENTRY)((ULONG_PTR)DirectoryBuffer + CurrentOffset);

        if (CurrentDirectoryEntry->direntlen == 0)
        {
            break;
        }

        if ((CurrentDirectoryEntry->direntlen + CurrentOffset) > DirectorySize)
        {
            FileSystemError("Directory entry extends past end of directory file.");
            return FALSE;
        }

        TRACE("Dumping directory entry at offset %d:\n", CurrentOffset);
        DbgDumpBuffer(DPRINT_FILESYSTEM, CurrentDirectoryEntry, CurrentDirectoryEntry->direntlen);

        if ((_strnicmp(FileName, CurrentDirectoryEntry->name, CurrentDirectoryEntry->namelen) == 0) &&
            (strlen(FileName) == CurrentDirectoryEntry->namelen))
        {
            RtlCopyMemory(DirectoryEntry, CurrentDirectoryEntry, sizeof(EXT2_DIR_ENTRY));

            TRACE("EXT2 Directory Entry:\n");
            TRACE("inode = %d\n", DirectoryEntry->inode);
            TRACE("direntlen = %d\n", DirectoryEntry->direntlen);
            TRACE("namelen = %d\n", DirectoryEntry->namelen);
            TRACE("filetype = %d\n", DirectoryEntry->filetype);
            TRACE("name = ");
            for (CurrentOffset=0; CurrentOffset<DirectoryEntry->namelen; CurrentOffset++)
            {
                TRACE("%c", DirectoryEntry->name[CurrentOffset]);
            }
            TRACE("\n");

            return TRUE;
        }

        CurrentOffset += CurrentDirectoryEntry->direntlen;
    }

    return FALSE;
}