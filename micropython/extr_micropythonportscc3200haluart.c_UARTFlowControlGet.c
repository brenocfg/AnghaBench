#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 unsigned long HWREG (scalar_t__) ; 
 int /*<<< orphan*/  UARTBaseValid (unsigned long) ; 
 unsigned long UART_FLOWCONTROL_RX ; 
 unsigned long UART_FLOWCONTROL_TX ; 
 scalar_t__ UART_O_CTL ; 

unsigned long
UARTFlowControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //

    ASSERT(UARTBaseValid(ulBase));

    return(HWREG(ulBase + UART_O_CTL) & (UART_FLOWCONTROL_TX |
                                         UART_FLOWCONTROL_RX));
}