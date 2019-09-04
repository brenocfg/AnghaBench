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
typedef  int ULONG ;
struct TYPE_8__ {scalar_t__ es; } ;
struct TYPE_7__ {int eax; } ;
struct TYPE_9__ {TYPE_2__ w; TYPE_1__ x; } ;
typedef  TYPE_3__ REGS ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INT386_SUCCESS (TYPE_3__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOLEAN
GetEbdaLocation(
    PULONG BaseAddress,
    PULONG Size)
{
    REGS Regs;

    TRACE("GetEbdaLocation()\n");

    /* Get the address of the Extended BIOS Data Area (EBDA).
     * Int 15h, AH=C1h
     * SYSTEM - RETURN EXTENDED-BIOS DATA-AREA SEGMENT ADDRESS (PS)
     *
     * Return:
     * CF set on error
     * CF clear if successful
     * ES = segment of data area
     */
    Regs.x.eax = 0x0000C100;
    Int386(0x15, &Regs, &Regs);

    /* If the function fails, there is no EBDA */
    if (!INT386_SUCCESS(Regs))
    {
        return FALSE;
    }

    /* Get Base address and (maximum) size */
    *BaseAddress = (ULONG)Regs.w.es << 4;
    *Size = 0xA0000 - *BaseAddress;
    return TRUE;
}