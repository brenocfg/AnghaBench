#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UINT32 ;
struct TYPE_11__ {int Attributes; scalar_t__ StartCluster; } ;
struct TYPE_10__ {int /*<<< orphan*/  FatType; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  int /*<<< orphan*/  PFAT_FILE_INFO ;
typedef  char* PCSTR ;
typedef  TYPE_2__ FAT_FILE_INFO ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/ * FatBufferDirectory (TYPE_1__*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  FatSearchDirectoryBufferForFile (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  FatXSearchDirectoryBufferForFile (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  FsGetFirstNameFromPath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FsGetNumPathParts (char*) ; 
 scalar_t__ ISFATX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

ARC_STATUS FatLookupFile(PFAT_VOLUME_INFO Volume, PCSTR FileName, PFAT_FILE_INFO FatFileInfoPointer)
{
    UINT32        i;
    ULONG        NumberOfPathParts;
    CHAR        PathPart[261];
    PVOID        DirectoryBuffer;
    ULONG        DirectoryStartCluster = 0;
    ULONG        DirectorySize;
    FAT_FILE_INFO    FatFileInfo;

    TRACE("FatLookupFile() FileName = %s\n", FileName);

    memset(FatFileInfoPointer, 0, sizeof(FAT_FILE_INFO));

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
        DirectoryBuffer = FatBufferDirectory(Volume, DirectoryStartCluster, &DirectorySize, (i == 0) );
        if (DirectoryBuffer == NULL)
        {
            return ENOMEM;
        }

        //
        // Search for file name in directory
        //
        if (ISFATX(Volume->FatType))
        {
            if (!FatXSearchDirectoryBufferForFile(Volume, DirectoryBuffer, DirectorySize, PathPart, &FatFileInfo))
            {
                return ENOENT;
            }
        }
        else
        {
            if (!FatSearchDirectoryBufferForFile(Volume, DirectoryBuffer, DirectorySize, PathPart, &FatFileInfo))
            {
                return ENOENT;
            }
        }

        //
        // If we have another sub-directory to go then
        // grab the start cluster and free the fat chain array
        //
        if ((i+1) < NumberOfPathParts)
        {
            //
            // Check if current entry is a directory
            //
            if (!(FatFileInfo.Attributes & ATTR_DIRECTORY))
            {
                return ENOTDIR;
            }
            DirectoryStartCluster = FatFileInfo.StartCluster;
        }
    }

    memcpy(FatFileInfoPointer, &FatFileInfo, sizeof(FAT_FILE_INFO));

    return ESUCCESS;
}