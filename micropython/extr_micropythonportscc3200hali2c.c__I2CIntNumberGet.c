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
typedef  scalar_t__ const uint32_t ;
typedef  size_t int_fast8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _I2CBaseValid (scalar_t__ const) ; 
 size_t g_i8I2CIntMapRows ; 
 scalar_t__** g_ppui32I2CIntMap ; 

__attribute__((used)) static uint32_t
_I2CIntNumberGet(uint32_t ui32Base)
{
    int_fast8_t i8Idx, i8Rows;
    const uint32_t (*ppui32I2CIntMap)[2];

    //
    // Check the arguments.
    //
    ASSERT(_I2CBaseValid(ui32Base));

    ppui32I2CIntMap = g_ppui32I2CIntMap;
    i8Rows = g_i8I2CIntMapRows;

    //
    // Loop through the table that maps I2C base addresses to interrupt
    // numbers.
    //
    for(i8Idx = 0; i8Idx < i8Rows; i8Idx++)
    {
        //
        // See if this base address matches.
        //
        if(ppui32I2CIntMap[i8Idx][0] == ui32Base)
        {
            //
            // Return the corresponding interrupt number.
            //
            return(ppui32I2CIntMap[i8Idx][1]);
        }
    }

    //
    // The base address could not be found, so return an error.
    //
    return(0);
}