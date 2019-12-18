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
 scalar_t__ DTHE_O_CRC_RSLT_PP ; 
 scalar_t__ HWREG (scalar_t__) ; 

uint32_t
CRCResultRead(uint32_t ui32Base)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == DTHE_BASE);

    //
    // return value.
    //
    return(HWREG(DTHE_BASE + DTHE_O_CRC_RSLT_PP));

}