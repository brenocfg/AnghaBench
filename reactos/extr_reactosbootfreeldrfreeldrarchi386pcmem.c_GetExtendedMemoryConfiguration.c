#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_10__ {int ax; int bx; int cx; int dx; } ;
struct TYPE_9__ {int eflags; } ;
struct TYPE_8__ {int ah; } ;
struct TYPE_11__ {TYPE_3__ w; TYPE_2__ x; TYPE_1__ b; } ;
typedef  TYPE_4__ REGS ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int EFLAGS_CF ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INT386_SUCCESS (TYPE_4__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_4__*,TYPE_4__*) ; 
 int READ_PORT_UCHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
BOOLEAN
GetExtendedMemoryConfiguration(ULONG* pMemoryAtOneMB /* in KB */, ULONG* pMemoryAtSixteenMB /* in 64KB */)
{
    REGS     RegsIn;
    REGS     RegsOut;

    TRACE("GetExtendedMemoryConfiguration()\n");

    *pMemoryAtOneMB = 0;
    *pMemoryAtSixteenMB = 0;

    // Int 15h AX=E801h
    // Phoenix BIOS v4.0 - GET MEMORY SIZE FOR >64M CONFIGURATIONS
    //
    // AX = E801h
    // Return:
    // CF clear if successful
    // AX = extended memory between 1M and 16M, in K (max 3C00h = 15MB)
    // BX = extended memory above 16M, in 64K blocks
    // CX = configured memory 1M to 16M, in K
    // DX = configured memory above 16M, in 64K blocks
    // CF set on error
    RegsIn.w.ax = 0xE801;
    Int386(0x15, &RegsIn, &RegsOut);

    TRACE("Int15h AX=E801h\n");
    TRACE("AX = 0x%x\n", RegsOut.w.ax);
    TRACE("BX = 0x%x\n", RegsOut.w.bx);
    TRACE("CX = 0x%x\n", RegsOut.w.cx);
    TRACE("DX = 0x%x\n", RegsOut.w.dx);
    TRACE("CF set = %s\n", (RegsOut.x.eflags & EFLAGS_CF) ? "TRUE" : "FALSE");

    if (INT386_SUCCESS(RegsOut))
    {
        // If AX=BX=0000h the use CX and DX
        if (RegsOut.w.ax == 0)
        {
            // Return extended memory size in K
            *pMemoryAtSixteenMB = RegsOut.w.dx;
            *pMemoryAtOneMB = RegsOut.w.cx;
            return TRUE;
        }
        else
        {
            // Return extended memory size in K
            *pMemoryAtSixteenMB = RegsOut.w.bx;
            *pMemoryAtOneMB = RegsOut.w.ax;
            return TRUE;
        }
    }

    // If we get here then Int15 Func E801h didn't work
    // So try Int15 Func 88h
    // Int 15h AH=88h
    // SYSTEM - GET EXTENDED MEMORY SIZE (286+)
    //
    // AH = 88h
    // Return:
    // CF clear if successful
    // AX = number of contiguous KB starting at absolute address 100000h
    // CF set on error
    // AH = status
    // 80h invalid command (PC,PCjr)
    // 86h unsupported function (XT,PS30)
    RegsIn.b.ah = 0x88;
    Int386(0x15, &RegsIn, &RegsOut);

    TRACE("Int15h AH=88h\n");
    TRACE("AX = 0x%x\n", RegsOut.w.ax);
    TRACE("CF set = %s\n", (RegsOut.x.eflags & EFLAGS_CF) ? "TRUE" : "FALSE");

    if (INT386_SUCCESS(RegsOut) && RegsOut.w.ax != 0)
    {
        *pMemoryAtOneMB = RegsOut.w.ax;
        return TRUE;
    }

    // If we get here then Int15 Func 88h didn't work
    // So try reading the CMOS
    WRITE_PORT_UCHAR((PUCHAR)0x70, 0x31);
    *pMemoryAtOneMB = READ_PORT_UCHAR((PUCHAR)0x71);
    *pMemoryAtOneMB = (*pMemoryAtOneMB & 0xFFFF);
    *pMemoryAtOneMB = (*pMemoryAtOneMB << 8);

    TRACE("Int15h Failed\n");
    TRACE("CMOS reports: 0x%lx\n", *pMemoryAtOneMB);

    if (*pMemoryAtOneMB != 0)
    {
        return TRUE;
    }

    return FALSE;
}