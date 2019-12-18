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
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long HWREG (scalar_t__) ; 
 unsigned long UARTA1_BASE ; 
 unsigned long UART_OUTPUT_RTS ; 
 scalar_t__ UART_O_CTL ; 

unsigned long
UARTModemControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ulBase == UARTA1_BASE);

    return(HWREG(ulBase + UART_O_CTL) & (UART_OUTPUT_RTS));
}