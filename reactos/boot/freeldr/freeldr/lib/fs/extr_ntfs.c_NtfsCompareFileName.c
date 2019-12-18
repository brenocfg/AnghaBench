#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_5__ {size_t FileNameLength; scalar_t__ FileNameType; scalar_t__* FileName; } ;
struct TYPE_6__ {TYPE_1__ FileName; } ;
typedef  scalar_t__* PWCHAR ;
typedef  TYPE_2__* PNTFS_INDEX_ENTRY ;
typedef  scalar_t__* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NTFS_FILE_NAME_POSIX ; 
 int /*<<< orphan*/  NtfsPrintFile (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t strlen (scalar_t__*) ; 
 scalar_t__ tolower (scalar_t__) ; 

__attribute__((used)) static BOOLEAN NtfsCompareFileName(PCHAR FileName, PNTFS_INDEX_ENTRY IndexEntry)
{
    PWCHAR EntryFileName;
    UCHAR EntryFileNameLength;
    UCHAR i;

    EntryFileName = IndexEntry->FileName.FileName;
    EntryFileNameLength = IndexEntry->FileName.FileNameLength;

#if DBG
    NtfsPrintFile(IndexEntry);
#endif

    if (strlen(FileName) != EntryFileNameLength)
        return FALSE;

    /* Do case-sensitive compares for Posix file names. */
    if (IndexEntry->FileName.FileNameType == NTFS_FILE_NAME_POSIX)
    {
        for (i = 0; i < EntryFileNameLength; i++)
            if (EntryFileName[i] != FileName[i])
                return FALSE;
    }
    else
    {
        for (i = 0; i < EntryFileNameLength; i++)
            if (tolower(EntryFileName[i]) != tolower(FileName[i]))
                return FALSE;
    }

    return TRUE;
}