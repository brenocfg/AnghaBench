#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_15__ {int Size; int Cylinders; int SectorsPerTrack; int BytesPerSector; scalar_t__ Heads; } ;
struct TYPE_14__ {int Cylinders; int Sectors; int BytesPerSector; scalar_t__ Heads; } ;
struct TYPE_12__ {int ah; int cl; scalar_t__ dh; scalar_t__ ch; int /*<<< orphan*/  dl; } ;
struct TYPE_11__ {int es; int di; } ;
struct TYPE_13__ {TYPE_2__ b; TYPE_1__ w; } ;
typedef  TYPE_3__ REGS ;
typedef  TYPE_4__* PGEOMETRY ;
typedef  int /*<<< orphan*/  ExtGeometry ;
typedef  TYPE_5__ EXTENDED_GEOMETRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ DiskGetExtendedDriveParameters (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INT386_SUCCESS (TYPE_3__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
PcDiskGetDriveGeometry(UCHAR DriveNumber, PGEOMETRY Geometry)
{
    EXTENDED_GEOMETRY ExtGeometry;
    REGS RegsIn, RegsOut;
    ULONG Cylinders;

    TRACE("DiskGetDriveGeometry()\n");

    /* Try to get the extended geometry first */
    ExtGeometry.Size = sizeof(ExtGeometry);
    if (DiskGetExtendedDriveParameters(DriveNumber, &ExtGeometry, ExtGeometry.Size))
    {
        Geometry->Cylinders = ExtGeometry.Cylinders;
        Geometry->Heads = ExtGeometry.Heads;
        Geometry->Sectors = ExtGeometry.SectorsPerTrack;
        Geometry->BytesPerSector = ExtGeometry.BytesPerSector;
        return TRUE;
    }

    /*
     * BIOS Int 13h, function 08h - Get drive parameters
     * AH = 08h
     * DL = drive (bit 7 set for hard disk)
     * ES:DI = 0000h:0000h to guard against BIOS bugs
     * Return:
     * CF set on error
     * AH = status (07h)
     * CF clear if successful
     * AH = 00h
     * AL = 00h on at least some BIOSes
     * BL = drive type (AT/PS2 floppies only)
     * CH = low eight bits of maximum cylinder number
     * CL = maximum sector number (bits 5-0)
     *      high two bits of maximum cylinder number (bits 7-6)
     * DH = maximum head number
     * DL = number of drives
     * ES:DI -> drive parameter table (floppies only)
     */
    RegsIn.b.ah = 0x08;
    RegsIn.b.dl = DriveNumber;
    RegsIn.w.es = 0x0000;
    RegsIn.w.di = 0x0000;

    /* Get drive parameters */
    Int386(0x13, &RegsIn, &RegsOut);
    if (!INT386_SUCCESS(RegsOut))
        return FALSE;

    Cylinders = (RegsOut.b.cl & 0xC0) << 2;
    Cylinders += RegsOut.b.ch;
    Cylinders++;
    Geometry->Cylinders = Cylinders;
    Geometry->Heads = RegsOut.b.dh + 1;
    Geometry->Sectors = RegsOut.b.cl & 0x3F;
    Geometry->BytesPerSector = 512;     /* Just assume 512 bytes per sector */

    return TRUE;
}