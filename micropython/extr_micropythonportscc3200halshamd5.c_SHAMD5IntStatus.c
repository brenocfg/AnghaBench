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
 scalar_t__ DTHE_BASE ; 
 scalar_t__ DTHE_O_SHA_MIS ; 
 scalar_t__ DTHE_O_SHA_RIS ; 
 scalar_t__ HWREG (scalar_t__) ; 
 scalar_t__ SHAMD5_BASE ; 
 scalar_t__ SHAMD5_O_IRQENABLE ; 
 scalar_t__ SHAMD5_O_IRQSTATUS ; 

uint32_t
SHAMD5IntStatus(uint32_t ui32Base, bool bMasked)
{
    uint32_t ui32Temp;
    uint32_t ui32IrqEnable;

    //
    // Check the arguments.
    //
    ASSERT(ui32Base == SHAMD5_BASE);

    //
    // Return the value of the IRQSTATUS register.
    //
    if(bMasked)
    {
        ui32Temp = HWREG(DTHE_BASE + DTHE_O_SHA_MIS);
        ui32IrqEnable = HWREG(ui32Base + SHAMD5_O_IRQENABLE);
        return((HWREG(ui32Base + SHAMD5_O_IRQSTATUS) &
                ui32IrqEnable) | (ui32Temp & 0x00000007) << 16);
    }
    else
    {
        ui32Temp = HWREG(DTHE_BASE + DTHE_O_SHA_RIS);
        return(HWREG(ui32Base + SHAMD5_O_IRQSTATUS) |
               (ui32Temp & 0x00000007) << 16);

    }
}