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
 int /*<<< orphan*/  GPIOBaseValid (unsigned long) ; 
 scalar_t__ GPIO_O_GPIO_DIR ; 
 unsigned long HWREG (scalar_t__) ; 

unsigned long
GPIODirModeGet(unsigned long ulPort, unsigned char ucPin)
{
    unsigned long ulDir;

    //
    // Check the arguments.
    //
    ASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin direction
    //
    ulDir = HWREG(ulPort + GPIO_O_GPIO_DIR);
    return(((ulDir & ucPin) ? 1 : 0));
}