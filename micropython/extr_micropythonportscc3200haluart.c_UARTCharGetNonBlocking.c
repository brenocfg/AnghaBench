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
 long HWREG (scalar_t__) ; 
 int /*<<< orphan*/  UARTBaseValid (unsigned long) ; 
 long UART_FR_RXFE ; 
 scalar_t__ UART_O_DR ; 
 scalar_t__ UART_O_FR ; 

long
UARTCharGetNonBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(!(HWREG(ulBase + UART_O_FR) & UART_FR_RXFE))
    {
        //
        // Read and return the next character.
        //
        return(HWREG(ulBase + UART_O_DR));
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        return(-1);
    }
}