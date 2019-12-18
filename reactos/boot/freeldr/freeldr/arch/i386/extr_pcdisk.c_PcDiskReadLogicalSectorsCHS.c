#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  int ULONG_PTR ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_12__ {int Sectors; int Heads; int Cylinders; int BytesPerSector; } ;
struct TYPE_10__ {int ah; int al; int ch; int cl; int dh; int dl; } ;
struct TYPE_9__ {int bx; scalar_t__ es; } ;
struct TYPE_11__ {TYPE_2__ b; TYPE_1__ w; } ;
typedef  TYPE_3__ REGS ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_4__ GEOMETRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DiskError (char*,int) ; 
 int /*<<< orphan*/  DiskGetErrorCodeString (int) ; 
 int /*<<< orphan*/  DiskResetController (int) ; 
 int /*<<< orphan*/  ERR (char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INT386_SUCCESS (TYPE_3__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  PcDiskGetDriveGeometry (int,TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN PcDiskReadLogicalSectorsCHS(UCHAR DriveNumber, ULONGLONG SectorNumber, ULONG SectorCount, PVOID Buffer)
{
    UCHAR PhysicalSector;
    UCHAR PhysicalHead;
    ULONG PhysicalTrack;
    GEOMETRY DriveGeometry;
    ULONG NumberOfSectorsToRead;
    REGS RegsIn, RegsOut;
    ULONG RetryCount;

    TRACE("PcDiskReadLogicalSectorsCHS()\n");

    /* Get the drive geometry */
    //
    // TODO: Cache this information for the given drive.
    //
    if (!PcDiskGetDriveGeometry(DriveNumber, &DriveGeometry) ||
        DriveGeometry.Sectors == 0 || DriveGeometry.Heads == 0)
    {
        return FALSE;
    }

    while (SectorCount)
    {
        /*
         * Calculate the physical disk offsets.
         * Note: DriveGeometry.Sectors < 64
         */
        PhysicalSector = 1 + (UCHAR)(SectorNumber % DriveGeometry.Sectors);
        PhysicalHead = (UCHAR)((SectorNumber / DriveGeometry.Sectors) % DriveGeometry.Heads);
        PhysicalTrack = (ULONG)((SectorNumber / DriveGeometry.Sectors) / DriveGeometry.Heads);

        /* Calculate how many sectors we need to read this round */
        if (PhysicalSector > 1)
        {
            if (SectorCount >= (DriveGeometry.Sectors - (PhysicalSector - 1)))
                NumberOfSectorsToRead = (DriveGeometry.Sectors - (PhysicalSector - 1));
            else
                NumberOfSectorsToRead = SectorCount;
        }
        else
        {
            if (SectorCount >= DriveGeometry.Sectors)
                NumberOfSectorsToRead = DriveGeometry.Sectors;
            else
                NumberOfSectorsToRead = SectorCount;
        }

        /* Make sure the read is within the geometry boundaries */
        if ((PhysicalHead >= DriveGeometry.Heads) ||
            (PhysicalTrack >= DriveGeometry.Cylinders) ||
            ((NumberOfSectorsToRead + PhysicalSector) > (DriveGeometry.Sectors + 1)) ||
            (PhysicalSector > DriveGeometry.Sectors))
        {
            DiskError("Disk read exceeds drive geometry limits.", 0);
            return FALSE;
        }

        /*
         * BIOS Int 13h, function 2 - Read Disk Sectors
         * AH = 02h
         * AL = number of sectors to read (must be nonzero)
         * CH = low eight bits of cylinder number
         * CL = sector number 1-63 (bits 0-5)
         *      high two bits of cylinder (bits 6-7, hard disk only)
         * DH = head number
         * DL = drive number (bit 7 set for hard disk)
         * ES:BX -> data buffer
         * Return:
         * CF set on error
         * if AH = 11h (corrected ECC error), AL = burst length
         * CF clear if successful
         * AH = status
         * AL = number of sectors transferred
         *  (only valid if CF set for some BIOSes)
         */
        RegsIn.b.ah = 0x02;
        RegsIn.b.al = (UCHAR)NumberOfSectorsToRead;
        RegsIn.b.ch = (PhysicalTrack & 0xFF);
        RegsIn.b.cl = (UCHAR)(PhysicalSector + ((PhysicalTrack & 0x300) >> 2));
        RegsIn.b.dh = PhysicalHead;
        RegsIn.b.dl = DriveNumber;
        RegsIn.w.es = (USHORT)(((ULONG_PTR)Buffer) >> 4);
        RegsIn.w.bx = ((ULONG_PTR)Buffer) & 0x0F;

        /* Perform the read. Retry 3 times. */
        for (RetryCount=0; RetryCount<3; RetryCount++)
        {
            Int386(0x13, &RegsIn, &RegsOut);

            /* If it worked break out */
            if (INT386_SUCCESS(RegsOut))
            {
                break;
            }
            /* If it was a corrected ECC error then the data is still good */
            else if (RegsOut.b.ah == 0x11)
            {
                break;
            }
            /* If it failed the do the next retry */
            else
            {
                DiskResetController(DriveNumber);
                continue;
            }
        }

        /* If we retried 3 times then fail */
        if (RetryCount >= 3)
        {
            DiskError("Disk Read Failed in CHS mode, after retrying 3 times", RegsOut.b.ah);
            ERR("Disk Read Failed in CHS mode, after retrying 3 times: %x (%s) (DriveNumber: 0x%x SectorNumber: %I64d SectorCount: %d)\n",
                RegsOut.b.ah, DiskGetErrorCodeString(RegsOut.b.ah),
                DriveNumber, SectorNumber, SectorCount);
            return FALSE;
        }

        // I have learned that not all BIOSes return
        // the sector read count in the AL register (at least mine doesn't)
        // even if the sectors were read correctly. So instead
        // of checking the sector read count we will rely solely
        // on the carry flag being set on error

        Buffer = (PVOID)((ULONG_PTR)Buffer + (NumberOfSectorsToRead * DriveGeometry.BytesPerSector));
        SectorCount -= NumberOfSectorsToRead;
        SectorNumber += NumberOfSectorsToRead;
    }

    return TRUE;
}