#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int cx; unsigned int dx; } ;
struct TYPE_6__ {int ah; } ;
struct TYPE_8__ {TYPE_2__ w; TYPE_1__ b; } ;
typedef  TYPE_3__ REGS ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_3__*,TYPE_3__*) ; 

void delay(unsigned msec)
{
    REGS        Regs;
    unsigned    usec;
    unsigned    msec_this;

    // Int 15h AH=86h
    // BIOS - WAIT (AT,PS)
    //
    // AH = 86h
    // CX:DX = interval in microseconds
    // Return:
    // CF clear if successful (wait interval elapsed)
    // CF set on error or AH=83h wait already in progress
    // AH = status (see #00496)

    // Note: The resolution of the wait period is 977 microseconds on
    // many systems because many BIOSes use the 1/1024 second fast
    // interrupt from the AT real-time clock chip which is available on INT 70;
    // because newer BIOSes may have much more precise timers available, it is
    // not possible to use this function accurately for very short delays unless
    // the precise behavior of the BIOS is known (or found through testing)

    while (msec)
    {
        msec_this = msec;

        if (msec_this > 4000)
        {
            msec_this = 4000;
        }

        usec = msec_this * 1000;

        Regs.b.ah = 0x86;
        Regs.w.cx = usec >> 16;
        Regs.w.dx = usec & 0xffff;
        Int386(0x15, &Regs, &Regs);

        msec -= msec_this;
    }
}