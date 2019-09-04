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
 scalar_t__ UART_O_CTL ; 
 unsigned long UART_TXINT_MODE_EOT ; 
 unsigned long UART_TXINT_MODE_FIFO ; 

unsigned long
UARTTxIntModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the current transmit interrupt mode.
    //
    return(HWREG(ulBase + UART_O_CTL) & (UART_TXINT_MODE_EOT |
                                         UART_TXINT_MODE_FIFO));
}