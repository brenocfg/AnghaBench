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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {scalar_t__ FilePointer; scalar_t__ FileSize; scalar_t__* FileFatChain; TYPE_1__* Volume; } ;
struct TYPE_6__ {scalar_t__ SectorsPerCluster; scalar_t__ BytesPerSector; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  TYPE_2__* PFAT_FILE_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatReadClusterChain (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FatReadPartialCluster (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN FatReadFile(PFAT_FILE_INFO FatFileInfo, ULONG BytesToRead, ULONG* BytesRead, PVOID Buffer)
{
    PFAT_VOLUME_INFO Volume = FatFileInfo->Volume;
    ULONG            ClusterNumber;
    ULONG            OffsetInCluster;
    ULONG            LengthInCluster;
    ULONG            NumberOfClusters;
    ULONG            BytesPerCluster;

    TRACE("FatReadFile() BytesToRead = %d Buffer = 0x%x\n", BytesToRead, Buffer);

    if (BytesRead != NULL)
    {
        *BytesRead = 0;
    }

    //
    // If they are trying to read past the
    // end of the file then return success
    // with BytesRead == 0
    //
    if (FatFileInfo->FilePointer >= FatFileInfo->FileSize)
    {
        return TRUE;
    }

    //
    // If they are trying to read more than there is to read
    // then adjust the amount to read
    //
    if ((FatFileInfo->FilePointer + BytesToRead) > FatFileInfo->FileSize)
    {
        BytesToRead = (FatFileInfo->FileSize - FatFileInfo->FilePointer);
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
    // | Cluster 1 | Cluster 2 | Cluster 3 | Cluster 4 |
    // +-----------+-----------+-----------+-----------+
    //    |                                    |
    //    +---------------+--------------------+
    //                    |
    // BytesToRead -------+
    //
    // 1 - The first calculation (and read) will align
    //     the file pointer with the next cluster.
    //     boundary (if we are supposed to read that much)
    // 2 - The next calculation (and read) will read
    //     in all the full clusters that the requested
    //     amount of data would cover (in this case
    //     clusters 2 & 3).
    // 3 - The last calculation (and read) would read
    //     in the remainder of the data requested out of
    //     the last cluster.
    //

    BytesPerCluster = Volume->SectorsPerCluster * Volume->BytesPerSector;

    //
    // Only do the first read if we
    // aren't aligned on a cluster boundary
    //
    if (FatFileInfo->FilePointer % BytesPerCluster)
    {
        //
        // Do the math for our first read
        //
        ClusterNumber = (FatFileInfo->FilePointer / BytesPerCluster);
        ClusterNumber = FatFileInfo->FileFatChain[ClusterNumber];
        OffsetInCluster = (FatFileInfo->FilePointer % BytesPerCluster);
        LengthInCluster = (BytesToRead > (BytesPerCluster - OffsetInCluster)) ? (BytesPerCluster - OffsetInCluster) : BytesToRead;

        //
        // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
        //
        if (!FatReadPartialCluster(Volume, ClusterNumber, OffsetInCluster, LengthInCluster, Buffer))
        {
            return FALSE;
        }
        if (BytesRead != NULL)
        {
            *BytesRead += LengthInCluster;
        }
        BytesToRead -= LengthInCluster;
        FatFileInfo->FilePointer += LengthInCluster;
        Buffer = (PVOID)((ULONG_PTR)Buffer + LengthInCluster);
    }

    //
    // Do the math for our second read (if any data left)
    //
    if (BytesToRead > 0)
    {
        //
        // Determine how many full clusters we need to read
        //
        NumberOfClusters = (BytesToRead / BytesPerCluster);

        if (NumberOfClusters > 0)
        {
            ClusterNumber = (FatFileInfo->FilePointer / BytesPerCluster);
            ClusterNumber = FatFileInfo->FileFatChain[ClusterNumber];

            //
            // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
            //
            if (!FatReadClusterChain(Volume, ClusterNumber, NumberOfClusters, Buffer))
            {
                return FALSE;
            }
            if (BytesRead != NULL)
            {
                *BytesRead += (NumberOfClusters * BytesPerCluster);
            }
            BytesToRead -= (NumberOfClusters * BytesPerCluster);
            FatFileInfo->FilePointer += (NumberOfClusters * BytesPerCluster);
            Buffer = (PVOID)((ULONG_PTR)Buffer + (NumberOfClusters * BytesPerCluster));
        }
    }

    //
    // Do the math for our third read (if any data left)
    //
    if (BytesToRead > 0)
    {
        ClusterNumber = (FatFileInfo->FilePointer / BytesPerCluster);
        ClusterNumber = FatFileInfo->FileFatChain[ClusterNumber];

        //
        // Now do the read and update BytesRead, BytesToRead, FilePointer, & Buffer
        //
        if (!FatReadPartialCluster(Volume, ClusterNumber, 0, BytesToRead, Buffer))
        {
            return FALSE;
        }
        if (BytesRead != NULL)
        {
            *BytesRead += BytesToRead;
        }
        FatFileInfo->FilePointer += BytesToRead;
        BytesToRead -= BytesToRead;
        Buffer = (PVOID)((ULONG_PTR)Buffer + BytesToRead);
    }

    return TRUE;
}