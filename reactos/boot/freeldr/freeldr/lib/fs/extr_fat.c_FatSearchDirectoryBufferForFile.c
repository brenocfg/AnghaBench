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
typedef  int ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_14__ {int Attributes; int FileSize; int CurrentCluster; int StartCluster; scalar_t__ FilePointer; } ;
struct TYPE_13__ {int SequenceNumber; int* Name0_4; int* Name5_10; int* Name11_12; } ;
struct TYPE_12__ {char* FileName; int Attr; int Size; int ClusterHigh; int ClusterLow; int ReservedNT; int TimeInTenths; int CreateTime; int CreateDate; int LastAccessDate; int Time; int Date; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_2__* PLFN_DIRENTRY ;
typedef  int /*<<< orphan*/  PFAT_VOLUME_INFO ;
typedef  TYPE_3__* PFAT_FILE_INFO ;
typedef  TYPE_1__* PDIRENTRY ;
typedef  scalar_t__* PCHAR ;
typedef  TYPE_2__ LFN_DIRENTRY ;
typedef  TYPE_1__ DIRENTRY ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int ATTR_LONG_NAME ; 
 int ATTR_VOLUMENAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatParseShortFileName (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FatSwapDirEntry (TYPE_1__*) ; 
 int /*<<< orphan*/  FatSwapLFNDirEntry (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _stricmp (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (scalar_t__*) ; 

BOOLEAN FatSearchDirectoryBufferForFile(PFAT_VOLUME_INFO Volume, PVOID DirectoryBuffer, ULONG DirectorySize, PCHAR FileName, PFAT_FILE_INFO FatFileInfoPointer)
{
    ULONG        EntryCount;
    ULONG        CurrentEntry;
    CHAR        LfnNameBuffer[265];
    CHAR        ShortNameBuffer[20];
    ULONG        StartCluster;
    DIRENTRY        OurDirEntry;
    LFN_DIRENTRY    OurLfnDirEntry;
    PDIRENTRY    DirEntry = &OurDirEntry;
    PLFN_DIRENTRY    LfnDirEntry = &OurLfnDirEntry;

    EntryCount = DirectorySize / sizeof(DIRENTRY);

    TRACE("FatSearchDirectoryBufferForFile() DirectoryBuffer = 0x%x EntryCount = %d FileName = %s\n", DirectoryBuffer, EntryCount, FileName);

    memset(ShortNameBuffer, 0, 13 * sizeof(CHAR));
    memset(LfnNameBuffer, 0, 261 * sizeof(CHAR));

    for (CurrentEntry=0; CurrentEntry<EntryCount; CurrentEntry++, DirectoryBuffer = ((PDIRENTRY)DirectoryBuffer)+1)
    {
        OurLfnDirEntry = *((PLFN_DIRENTRY) DirectoryBuffer);
        FatSwapLFNDirEntry(LfnDirEntry);
        OurDirEntry = *((PDIRENTRY) DirectoryBuffer);
        FatSwapDirEntry(DirEntry);

        //TRACE("Dumping directory entry %d:\n", CurrentEntry);
        //DbgDumpBuffer(DPRINT_FILESYSTEM, DirEntry, sizeof(DIRENTRY));

        //
        // Check if this is the last file in the directory
        // If DirEntry[0] == 0x00 then that means all the
        // entries after this one are unused. If this is the
        // last entry then we didn't find the file in this directory.
        //
        if (DirEntry->FileName[0] == '\0')
        {
            return FALSE;
        }

        //
        // Check if this is a deleted entry or not
        //
        if (DirEntry->FileName[0] == '\xE5')
        {
            memset(ShortNameBuffer, 0, 13 * sizeof(CHAR));
            memset(LfnNameBuffer, 0, 261 * sizeof(CHAR));
            continue;
        }

        //
        // Check if this is a LFN entry
        // If so it needs special handling
        //
        if (DirEntry->Attr == ATTR_LONG_NAME)
        {
            //
            // Check to see if this is a deleted LFN entry, if so continue
            //
            if (LfnDirEntry->SequenceNumber & 0x80)
            {
                continue;
            }

            //
            // Mask off high two bits of sequence number
            // and make the sequence number zero-based
            //
            LfnDirEntry->SequenceNumber &= 0x3F;
            LfnDirEntry->SequenceNumber--;

            //
            // Get all 13 LFN entry characters
            //
            if (LfnDirEntry->Name0_4[0] != 0xFFFF)
            {
                LfnNameBuffer[0 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name0_4[0];
            }
            if (LfnDirEntry->Name0_4[1] != 0xFFFF)
            {
                LfnNameBuffer[1 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name0_4[1];
            }
            if (LfnDirEntry->Name0_4[2] != 0xFFFF)
            {
                LfnNameBuffer[2 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name0_4[2];
            }
            if (LfnDirEntry->Name0_4[3] != 0xFFFF)
            {
                LfnNameBuffer[3 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name0_4[3];
            }
            if (LfnDirEntry->Name0_4[4] != 0xFFFF)
            {
                LfnNameBuffer[4 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name0_4[4];
            }
            if (LfnDirEntry->Name5_10[0] != 0xFFFF)
            {
                LfnNameBuffer[5 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[0];
            }
            if (LfnDirEntry->Name5_10[1] != 0xFFFF)
            {
                LfnNameBuffer[6 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[1];
            }
            if (LfnDirEntry->Name5_10[2] != 0xFFFF)
            {
                LfnNameBuffer[7 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[2];
            }
            if (LfnDirEntry->Name5_10[3] != 0xFFFF)
            {
                LfnNameBuffer[8 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[3];
            }
            if (LfnDirEntry->Name5_10[4] != 0xFFFF)
            {
                LfnNameBuffer[9 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[4];
            }
            if (LfnDirEntry->Name5_10[5] != 0xFFFF)
            {
                LfnNameBuffer[10 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name5_10[5];
            }
            if (LfnDirEntry->Name11_12[0] != 0xFFFF)
            {
                LfnNameBuffer[11 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name11_12[0];
            }
            if (LfnDirEntry->Name11_12[1] != 0xFFFF)
            {
                LfnNameBuffer[12 + (LfnDirEntry->SequenceNumber * 13)] = (UCHAR)LfnDirEntry->Name11_12[1];
            }

            //TRACE("Dumping long name buffer:\n");
            //DbgDumpBuffer(DPRINT_FILESYSTEM, LfnNameBuffer, 260);

            continue;
        }

        //
        // Check for the volume label attribute
        // and skip over this entry if found
        //
        if (DirEntry->Attr & ATTR_VOLUMENAME)
        {
            memset(ShortNameBuffer, 0, 13 * sizeof(UCHAR));
            memset(LfnNameBuffer, 0, 261 * sizeof(UCHAR));
            continue;
        }

        //
        // If we get here then we've found a short file name
        // entry and LfnNameBuffer contains the long file
        // name or zeroes. All we have to do now is see if the
        // file name matches either the short or long file name
        // and fill in the FAT_FILE_INFO structure if it does
        // or zero our buffers and continue looking.
        //

        //
        // Get short file name
        //
        FatParseShortFileName(ShortNameBuffer, DirEntry);

        //TRACE("Entry: %d LFN = %s\n", CurrentEntry, LfnNameBuffer);
        //TRACE("Entry: %d DOS name = %s\n", CurrentEntry, ShortNameBuffer);

        //
        // See if the file name matches either the short or long name
        //
        if (((strlen(FileName) == strlen(LfnNameBuffer)) && (_stricmp(FileName, LfnNameBuffer) == 0)) ||
            ((strlen(FileName) == strlen(ShortNameBuffer)) && (_stricmp(FileName, ShortNameBuffer) == 0)))        {
            //
            // We found the entry, now fill in the FAT_FILE_INFO struct
            //
            FatFileInfoPointer->Attributes = DirEntry->Attr;
            FatFileInfoPointer->FileSize = DirEntry->Size;
            FatFileInfoPointer->FilePointer = 0;
            StartCluster = ((ULONG)DirEntry->ClusterHigh << 16) + DirEntry->ClusterLow;
            FatFileInfoPointer->CurrentCluster = StartCluster;
            FatFileInfoPointer->StartCluster = StartCluster;

            TRACE("MSDOS Directory Entry:\n");
            TRACE("FileName[11] = %c%c%c%c%c%c%c%c%c%c%c\n", DirEntry->FileName[0], DirEntry->FileName[1], DirEntry->FileName[2], DirEntry->FileName[3], DirEntry->FileName[4], DirEntry->FileName[5], DirEntry->FileName[6], DirEntry->FileName[7], DirEntry->FileName[8], DirEntry->FileName[9], DirEntry->FileName[10]);
            TRACE("Attr = 0x%x\n", DirEntry->Attr);
            TRACE("ReservedNT = 0x%x\n", DirEntry->ReservedNT);
            TRACE("TimeInTenths = %d\n", DirEntry->TimeInTenths);
            TRACE("CreateTime = %d\n", DirEntry->CreateTime);
            TRACE("CreateDate = %d\n", DirEntry->CreateDate);
            TRACE("LastAccessDate = %d\n", DirEntry->LastAccessDate);
            TRACE("ClusterHigh = 0x%x\n", DirEntry->ClusterHigh);
            TRACE("Time = %d\n", DirEntry->Time);
            TRACE("Date = %d\n", DirEntry->Date);
            TRACE("ClusterLow = 0x%x\n", DirEntry->ClusterLow);
            TRACE("Size = %d\n", DirEntry->Size);
            TRACE("StartCluster = 0x%x\n", StartCluster);

            return TRUE;
        }

        //
        // Nope, no match - zero buffers and continue looking
        //
        memset(ShortNameBuffer, 0, 13 * sizeof(UCHAR));
        memset(LfnNameBuffer, 0, 261 * sizeof(UCHAR));
        continue;
    }

    return FALSE;
}