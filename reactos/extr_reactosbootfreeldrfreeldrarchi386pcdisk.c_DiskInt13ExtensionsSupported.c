#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UCHAR ;
struct TYPE_8__ {int bx; int cx; } ;
struct TYPE_7__ {int ah; int dl; } ;
struct TYPE_9__ {TYPE_2__ w; TYPE_1__ b; } ;
typedef  TYPE_3__ REGS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INT386_SUCCESS (TYPE_3__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOLEAN DiskInt13ExtensionsSupported(UCHAR DriveNumber)
{
    static UCHAR LastDriveNumber = 0xff;
    static BOOLEAN LastSupported;
    REGS RegsIn, RegsOut;

    TRACE("DiskInt13ExtensionsSupported()\n");

    if (DriveNumber == LastDriveNumber)
    {
        TRACE("Using cached value %s for drive 0x%x\n",
              LastSupported ? "TRUE" : "FALSE", DriveNumber);
        return LastSupported;
    }

    /*
     * Some BIOSes report that extended disk access functions are not supported
     * when booting from a CD (e.g. Phoenix BIOS v6.00PG and Insyde BIOS shipping
     * with Intel Macs). Therefore we just return TRUE if we're booting from a CD -
     * we can assume that all El Torito capable BIOSes support INT 13 extensions.
     * We simply detect whether we're booting from CD by checking whether the drive
     * number is >= 0x8A. It's 0x90 on the Insyde BIOS, and 0x9F on most other BIOSes.
     */
    if (DriveNumber >= 0x8A)
    {
        LastSupported = TRUE;
        return TRUE;
    }

    LastDriveNumber = DriveNumber;

    /*
     * IBM/MS INT 13 Extensions - INSTALLATION CHECK
     * AH = 41h
     * BX = 55AAh
     * DL = drive (80h-FFh)
     * Return:
     * CF set on error (extensions not supported)
     * AH = 01h (invalid function)
     * CF clear if successful
     * BX = AA55h if installed
     * AH = major version of extensions
     * 01h = 1.x
     * 20h = 2.0 / EDD-1.0
     * 21h = 2.1 / EDD-1.1
     * 30h = EDD-3.0
     * AL = internal use
     * CX = API subset support bitmap
     * DH = extension version (v2.0+ ??? -- not present in 1.x)
     *
     * Bitfields for IBM/MS INT 13 Extensions API support bitmap
     * Bit 0, extended disk access functions (AH=42h-44h,47h,48h) supported
     * Bit 1, removable drive controller functions (AH=45h,46h,48h,49h,INT 15/AH=52h) supported
     * Bit 2, enhanced disk drive (EDD) functions (AH=48h,AH=4Eh) supported
     *        extended drive parameter table is valid
     * Bits 3-15 reserved
     */
    RegsIn.b.ah = 0x41;
    RegsIn.w.bx = 0x55AA;
    RegsIn.b.dl = DriveNumber;

    /* Reset the disk controller */
    Int386(0x13, &RegsIn, &RegsOut);

    if (!INT386_SUCCESS(RegsOut))
    {
        /* CF set on error (extensions not supported) */
        LastSupported = FALSE;
        return FALSE;
    }

    if (RegsOut.w.bx != 0xAA55)
    {
        /* BX = AA55h if installed */
        LastSupported = FALSE;
        return FALSE;
    }

    if (!(RegsOut.w.cx & 0x0001))
    {
        /*
         * CX = API subset support bitmap.
         * Bit 0, extended disk access functions (AH=42h-44h,47h,48h) supported.
         */
        DbgPrint("Suspicious API subset support bitmap 0x%x on device 0x%lx\n",
                 RegsOut.w.cx, DriveNumber);
        LastSupported = FALSE;
        return FALSE;
    }

    LastSupported = TRUE;
    return TRUE;
}