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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ HWREG (scalar_t__) ; 
 scalar_t__ I2C_O_SCSR ; 
 int /*<<< orphan*/  _I2CBaseValid (scalar_t__) ; 

uint32_t
I2CSlaveStatus(uint32_t ui32Base)
{
    //
    // Check the arguments.
    //
    ASSERT(_I2CBaseValid(ui32Base));

    //
    // Return the slave status.
    //
    return(HWREG(ui32Base + I2C_O_SCSR));
}