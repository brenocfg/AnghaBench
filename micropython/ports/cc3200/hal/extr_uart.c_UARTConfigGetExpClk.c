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
 int HWREG (scalar_t__) ; 
 int /*<<< orphan*/  UARTBaseValid (unsigned long) ; 
 int UART_CTL_HSE ; 
 int UART_LCRH_EPS ; 
 int UART_LCRH_PEN ; 
 int UART_LCRH_SPS ; 
 int UART_LCRH_STP2 ; 
 int UART_LCRH_WLEN_M ; 
 scalar_t__ UART_O_CTL ; 
 scalar_t__ UART_O_FBRD ; 
 scalar_t__ UART_O_IBRD ; 
 scalar_t__ UART_O_LCRH ; 

void
UARTConfigGetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                    unsigned long *pulBaud, unsigned long *pulConfig)
{
    unsigned long ulInt, ulFrac;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Compute the baud rate.
    //
    ulInt = HWREG(ulBase + UART_O_IBRD);
    ulFrac = HWREG(ulBase + UART_O_FBRD);
    *pulBaud = (ulUARTClk * 4) / ((64 * ulInt) + ulFrac);

    //
    // See if high speed mode enabled.
    //
    if(HWREG(ulBase + UART_O_CTL) & UART_CTL_HSE)
    {
        //
        // High speed mode is enabled so the actual baud rate is actually
        // double what was just calculated.
        //
        *pulBaud *= 2;
    }

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = (HWREG(ulBase + UART_O_LCRH) &
                  (UART_LCRH_SPS | UART_LCRH_WLEN_M | UART_LCRH_STP2 |
                   UART_LCRH_EPS | UART_LCRH_PEN));
}