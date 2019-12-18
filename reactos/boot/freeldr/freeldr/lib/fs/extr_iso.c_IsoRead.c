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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_5__ {int FilePointer; int FileSize; int FileStart; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PISO_FILE_INFO ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ ArcRead (scalar_t__,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 scalar_t__ ArcSeek (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EIO ; 
 scalar_t__ ESUCCESS ; 
 scalar_t__ FsGetDeviceId (scalar_t__) ; 
 TYPE_1__* FsGetDeviceSpecific (scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int SECTORSIZE ; 
 int /*<<< orphan*/  SeekAbsolute ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ min (scalar_t__,int) ; 

ARC_STATUS IsoRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    ARC_STATUS Status;
    PISO_FILE_INFO FileHandle = FsGetDeviceSpecific(FileId);
    UCHAR SectorBuffer[SECTORSIZE];
    LARGE_INTEGER Position;
    ULONG DeviceId;
    ULONG SectorNumber;
    ULONG OffsetInSector;
    ULONG LengthInSector;
    ULONG NumberOfSectors;
    ULONG BytesRead;

    TRACE("IsoRead() Buffer = %p, N = %lu\n", Buffer, N);

    DeviceId = FsGetDeviceId(FileId);
    *Count = 0;

    //
    // If the user is trying to read past the end of
    // the file then return success with Count == 0.
    //
    if (FileHandle->FilePointer >= FileHandle->FileSize)
    {
        return ESUCCESS;
    }

    //
    // If the user is trying to read more than there is to read
    // then adjust the amount to read.
    //
    if (FileHandle->FilePointer + N > FileHandle->FileSize)
    {
        N = FileHandle->FileSize - FileHandle->FilePointer;
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
    // | Sector  1 | Sector  2 | Sector  3 | Sector  4 |
    // +-----------+-----------+-----------+-----------+
    //    |                                    |
    //    +---------------+--------------------+
    //                    |
    // N -----------------+
    //
    // 1 - The first calculation (and read) will align
    //     the file pointer with the next sector
    //     boundary (if we are supposed to read that much)
    // 2 - The next calculation (and read) will read
    //     in all the full sectors that the requested
    //     amount of data would cover (in this case
    //     sectors 2 & 3).
    // 3 - The last calculation (and read) would read
    //     in the remainder of the data requested out of
    //     the last sector.
    //


    //
    // Only do the first read if we
    // aren't aligned on a cluster boundary
    //
    if (FileHandle->FilePointer % SECTORSIZE)
    {
        //
        // Do the math for our first read
        //
        SectorNumber = FileHandle->FileStart + (FileHandle->FilePointer / SECTORSIZE);
        OffsetInSector = FileHandle->FilePointer % SECTORSIZE;
        LengthInSector = min(N, SECTORSIZE - OffsetInSector);

        //
        // Now do the read and update Count, N, FilePointer, & Buffer
        //
        Position.HighPart = 0;
        Position.LowPart = SectorNumber * SECTORSIZE;
        Status = ArcSeek(DeviceId, &Position, SeekAbsolute);
        if (Status != ESUCCESS)
        {
            return Status;
        }
        Status = ArcRead(DeviceId, SectorBuffer, SECTORSIZE, &BytesRead);
        if (Status != ESUCCESS || BytesRead != SECTORSIZE)
        {
            return EIO;
        }
        RtlCopyMemory(Buffer, SectorBuffer + OffsetInSector, LengthInSector);
        *Count += LengthInSector;
        N -= LengthInSector;
        FileHandle->FilePointer += LengthInSector;
        Buffer = (PVOID)((ULONG_PTR)Buffer + LengthInSector);
    }

    //
    // Do the math for our second read (if any data left)
    //
    if (N > 0)
    {
        //
        // Determine how many full clusters we need to read
        //
        NumberOfSectors = (N / SECTORSIZE);

        SectorNumber = FileHandle->FileStart + (FileHandle->FilePointer / SECTORSIZE);

        //
        // Now do the read and update Count, N, FilePointer, & Buffer
        //
        Position.HighPart = 0;
        Position.LowPart = SectorNumber * SECTORSIZE;
        Status = ArcSeek(DeviceId, &Position, SeekAbsolute);
        if (Status != ESUCCESS)
        {
            return Status;
        }
        Status = ArcRead(DeviceId, Buffer, NumberOfSectors * SECTORSIZE, &BytesRead);
        if (Status != ESUCCESS || BytesRead != NumberOfSectors * SECTORSIZE)
        {
            return EIO;
        }

        *Count += NumberOfSectors * SECTORSIZE;
        N -= NumberOfSectors * SECTORSIZE;
        FileHandle->FilePointer += NumberOfSectors * SECTORSIZE;
        Buffer = (PVOID)((ULONG_PTR)Buffer + NumberOfSectors * SECTORSIZE);
    }

    //
    // Do the math for our third read (if any data left)
    //
    if (N > 0)
    {
        SectorNumber = FileHandle->FileStart + (FileHandle->FilePointer / SECTORSIZE);

        //
        // Now do the read and update Count, N, FilePointer, & Buffer
        //
        Position.HighPart = 0;
        Position.LowPart = SectorNumber * SECTORSIZE;
        Status = ArcSeek(DeviceId, &Position, SeekAbsolute);
        if (Status != ESUCCESS)
        {
            return Status;
        }
        Status = ArcRead(DeviceId, SectorBuffer, SECTORSIZE, &BytesRead);
        if (Status != ESUCCESS || BytesRead != SECTORSIZE)
        {
            return EIO;
        }
        RtlCopyMemory(Buffer, SectorBuffer, N);
        *Count += N;
        FileHandle->FilePointer += N;
    }

    TRACE("IsoRead() done\n");

    return ESUCCESS;
}