#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG_PTR ;
struct TYPE_6__ {int mode; } ;
struct TYPE_7__ {int /*<<< orphan*/ * FileBlockList; int /*<<< orphan*/  FileSize; TYPE_1__ Inode; } ;
typedef  int /*<<< orphan*/  SymLinkPath ;
typedef  int /*<<< orphan*/ * PEXT2_FILE_INFO ;
typedef  char* PCSTR ;
typedef  TYPE_2__ EXT2_FILE_INFO ;
typedef  char CHAR ;

/* Variables and functions */
 int EXT2_NAME_LEN ; 
 int EXT2_S_IFLNK ; 
 int EXT2_S_IFMT ; 
 int /*<<< orphan*/  Ext2LookupFile (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  Ext2ReadFileBig (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (char*,int) ; 
 int /*<<< orphan*/  TAG_EXT_BLOCK_LIST ; 
 int /*<<< orphan*/  TAG_EXT_FILE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

PEXT2_FILE_INFO Ext2OpenFile(PCSTR FileName)
{
    EXT2_FILE_INFO        TempExt2FileInfo;
    PEXT2_FILE_INFO        FileHandle;
    CHAR            SymLinkPath[EXT2_NAME_LEN];
    CHAR            FullPath[EXT2_NAME_LEN * 2];
    ULONG_PTR        Index;

    TRACE("Ext2OpenFile() FileName = %s\n", FileName);

    RtlZeroMemory(SymLinkPath, sizeof(SymLinkPath));

    // Lookup the file in the file system
    if (!Ext2LookupFile(FileName, &TempExt2FileInfo))
    {
        return NULL;
    }

    // If we got a symbolic link then fix up the path
    // and re-call this function
    if ((TempExt2FileInfo.Inode.mode & EXT2_S_IFMT) == EXT2_S_IFLNK)
    {
        TRACE("File is a symbolic link\n");

        // Now read in the symbolic link path
        if (!Ext2ReadFileBig(&TempExt2FileInfo, TempExt2FileInfo.FileSize, NULL, SymLinkPath))
        {
            if (TempExt2FileInfo.FileBlockList != NULL)
            {
                FrLdrTempFree(TempExt2FileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
            }

            return NULL;
        }

        TRACE("Symbolic link path = %s\n", SymLinkPath);

        // Get the full path
        if (SymLinkPath[0] == '/' || SymLinkPath[0] == '\\')
        {
            // Symbolic link is an absolute path
            // So copy it to FullPath, but skip over
            // the '/' char at the beginning
            strcpy(FullPath, &SymLinkPath[1]);
        }
        else
        {
            // Symbolic link is a relative path
            // Copy the first part of the path
            strcpy(FullPath, FileName);

            // Remove the last part of the path
            for (Index=strlen(FullPath); Index>0; )
            {
                Index--;
                if (FullPath[Index] == '/' || FullPath[Index] == '\\')
                {
                    break;
                }
            }
            FullPath[Index] = '\0';

            // Concatenate the symbolic link
            strcat(FullPath, Index == 0 ? "" : "/");
            strcat(FullPath, SymLinkPath);
        }

        TRACE("Full file path = %s\n", FullPath);

        if (TempExt2FileInfo.FileBlockList != NULL)
        {
            FrLdrTempFree(TempExt2FileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
        }

        return Ext2OpenFile(FullPath);
    }
    else
    {
        FileHandle = FrLdrTempAlloc(sizeof(EXT2_FILE_INFO), TAG_EXT_FILE);

        if (FileHandle == NULL)
        {
            if (TempExt2FileInfo.FileBlockList != NULL)
            {
                FrLdrTempFree(TempExt2FileInfo.FileBlockList, TAG_EXT_BLOCK_LIST);
            }

            return NULL;
        }

        RtlCopyMemory(FileHandle, &TempExt2FileInfo, sizeof(EXT2_FILE_INFO));

        return FileHandle;
    }
}