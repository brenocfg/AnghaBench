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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
typedef  int /*<<< orphan*/  PNTFS_VOLUME_INFO ;
typedef  int /*<<< orphan*/  PNTFS_MFT_RECORD ;
typedef  int /*<<< orphan*/ * PNTFS_ATTR_CONTEXT ;
typedef  char* PCSTR ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FsGetFirstNameFromPath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FsGetNumPathParts (char*) ; 
 int /*<<< orphan*/  NTFS_ATTR_TYPE_DATA ; 
 int /*<<< orphan*/  NTFS_FILE_ROOT ; 
 int /*<<< orphan*/ * NtfsFindAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NtfsFindMftRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtfsReadMftRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN NtfsLookupFile(PNTFS_VOLUME_INFO Volume, PCSTR FileName, PNTFS_MFT_RECORD MftRecord, PNTFS_ATTR_CONTEXT *DataContext)
{
    ULONG NumberOfPathParts;
    CHAR PathPart[261];
    ULONGLONG CurrentMFTIndex;
    UCHAR i;

    TRACE("NtfsLookupFile() FileName = %s\n", FileName);

    CurrentMFTIndex = NTFS_FILE_ROOT;
    NumberOfPathParts = FsGetNumPathParts(FileName);
    for (i = 0; i < NumberOfPathParts; i++)
    {
        FsGetFirstNameFromPath(PathPart, FileName);

        for (; (*FileName != '\\') && (*FileName != '/') && (*FileName != '\0'); FileName++)
            ;
        FileName++;

        TRACE("- Lookup: %s\n", PathPart);
        if (!NtfsFindMftRecord(Volume, CurrentMFTIndex, PathPart, &CurrentMFTIndex))
        {
            TRACE("- Failed\n");
            return FALSE;
        }
        TRACE("- Lookup: %x\n", CurrentMFTIndex);
    }

    if (!NtfsReadMftRecord(Volume, CurrentMFTIndex, MftRecord))
    {
        TRACE("NtfsLookupFile: Can't read MFT record\n");
        return FALSE;
    }

    *DataContext = NtfsFindAttribute(Volume, MftRecord, NTFS_ATTR_TYPE_DATA, L"");
    if (*DataContext == NULL)
    {
        TRACE("NtfsLookupFile: Can't find data attribute\n");
        return FALSE;
    }

    return TRUE;
}