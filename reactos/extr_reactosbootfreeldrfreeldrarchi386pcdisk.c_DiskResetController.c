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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int ah; int /*<<< orphan*/  dl; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
typedef  TYPE_2__ REGS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  INT386_SUCCESS (TYPE_2__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

BOOLEAN DiskResetController(UCHAR DriveNumber)
{
    REGS RegsIn, RegsOut;

    WARN("DiskResetController(0x%x) DISK OPERATION FAILED -- RESETTING CONTROLLER\n", DriveNumber);

    /*
     * BIOS Int 13h, function 0 - Reset disk system
     * AH = 00h
     * DL = drive (if bit 7 is set both hard disks and floppy disks reset)
     * Return:
     * AH = status
     * CF clear if successful
     * CF set on error
     */
    RegsIn.b.ah = 0x00;
    RegsIn.b.dl = DriveNumber;

    /* Reset the disk controller */
    Int386(0x13, &RegsIn, &RegsOut);

    return INT386_SUCCESS(RegsOut);
}