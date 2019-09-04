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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int HWREG (int) ; 
 int I2C_MASTER_ERR_NONE ; 
 int I2C_MCS_ACK ; 
 int I2C_MCS_ADRACK ; 
 int I2C_MCS_ARBLST ; 
 int I2C_MCS_BUSY ; 
 int I2C_MCS_ERROR ; 
 int I2C_O_MCS ; 
 int /*<<< orphan*/  _I2CBaseValid (int) ; 

uint32_t
I2CMasterErr(uint32_t ui32Base)
{
    uint32_t ui32Err;

    //
    // Check the arguments.
    //
    ASSERT(_I2CBaseValid(ui32Base));

    //
    // Get the raw error state
    //
    ui32Err = HWREG(ui32Base + I2C_O_MCS);

    //
    // If the I2C master is busy, then all the other bit are invalid, and
    // don't have an error to report.
    //
    if(ui32Err & I2C_MCS_BUSY)
    {
        return(I2C_MASTER_ERR_NONE);
    }

    //
    // Check for errors.
    //
    if(ui32Err & (I2C_MCS_ERROR | I2C_MCS_ARBLST))
    {
        return(ui32Err & (I2C_MCS_ARBLST | I2C_MCS_ACK | I2C_MCS_ADRACK));
    }
    else
    {
        return(I2C_MASTER_ERR_NONE);
    }
}