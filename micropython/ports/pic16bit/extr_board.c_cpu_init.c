#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ PLLPRE; scalar_t__ PLLPOST; } ;
struct TYPE_3__ {int COSC; int /*<<< orphan*/  LOCK; } ;

/* Variables and functions */
 TYPE_2__ CLKDIVbits ; 
 TYPE_1__ OSCCONbits ; 
 scalar_t__ OSCTUN ; 
 int PLLFBD ; 
 int /*<<< orphan*/  __builtin_write_OSCCONH (int) ; 
 int /*<<< orphan*/  __builtin_write_OSCCONL (int) ; 

void cpu_init(void) {
    // set oscillator to operate at 40MHz
    // Fosc = Fin*M/(N1*N2), Fcy = Fosc/2
    // Fosc = 7.37M*40/(2*2) = 80Mhz for 7.37M input clock
    PLLFBD = 41;            // M=39
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE = 0;  // N2=2
    OSCTUN = 0;

    // initiate clock switch to FRC with PLL
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);

    // wait for clock switch to occur
    while (OSCCONbits.COSC != 0x01) {
    }
    while (!OSCCONbits.LOCK) {
    }
}