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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DES_BASE ; 
 scalar_t__ DES_O_IRQENABLE ; 
 scalar_t__ DES_O_IRQSTATUS ; 
 scalar_t__ DTHE_BASE ; 
 scalar_t__ DTHE_O_DES_MIS ; 
 int HWREG (scalar_t__) ; 

uint32_t
DESIntStatus(uint32_t ui32Base, bool bMasked)
{
   uint32_t ui32IntStatus;
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == DES_BASE);

    //
    // Read the status register and return the value.
    //
    if(bMasked)
    {
        ui32IntStatus = HWREG(ui32Base + DES_O_IRQSTATUS);
        ui32IntStatus &= HWREG(ui32Base + DES_O_IRQENABLE);
        ui32IntStatus |= ((HWREG(DTHE_BASE + DTHE_O_DES_MIS) & 0x7) << 16);

        return(ui32IntStatus);
    }
    else
    {
        ui32IntStatus = HWREG(ui32Base + DES_O_IRQSTATUS);
        ui32IntStatus |= ((HWREG(DTHE_BASE + DTHE_O_DES_MIS) & 0xD) << 16);
        return(ui32IntStatus);
    }
}