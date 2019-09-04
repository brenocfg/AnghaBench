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
typedef  scalar_t__ tBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOBaseValid (unsigned long) ; 
 scalar_t__ GPIO_O_GPIO_MIS ; 
 scalar_t__ GPIO_O_GPIO_RIS ; 
 long HWREG (scalar_t__) ; 

long
GPIOIntStatus(unsigned long ulPort, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT(GPIOBaseValid(ulPort));

    //
    // Return the interrupt status.
    //
    if(bMasked)
    {
        return(HWREG(ulPort + GPIO_O_GPIO_MIS));
    }
    else
    {
        return(HWREG(ulPort + GPIO_O_GPIO_RIS));
    }
}