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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DES_BASE ; 
 scalar_t__ DES_CTRL_OUTPUT_READY ; 
 scalar_t__ DES_O_CTRL ; 
 scalar_t__ DES_O_DATA_H ; 
 scalar_t__ DES_O_DATA_L ; 
 scalar_t__ HWREG (scalar_t__) ; 

void
DESDataRead(uint32_t ui32Base, uint8_t *pui8Dest, uint8_t ui8Length)
{
	volatile uint32_t pui32Dest[2];
	uint8_t ui8BytCnt;
	uint8_t *pui8DestTemp;

	//
	// Check the arguments.
	//
	ASSERT(ui32Base == DES_BASE);
	if((ui8Length == 0)||(ui8Length>8))
	{
		return;
	}
    //
    // Wait for data output to be ready.
    //
    while((HWREG(ui32Base + DES_O_CTRL) & DES_CTRL_OUTPUT_READY) == 0)
    {
    }

    //
    // Read two words of data from the data registers.
    //
    pui32Dest[0] = HWREG(DES_BASE + DES_O_DATA_L);
    pui32Dest[1] = HWREG(DES_BASE + DES_O_DATA_H);

    //
    //Copy the data to a block memory
    //
    pui8DestTemp = (uint8_t *)pui32Dest;
    for(ui8BytCnt = 0; ui8BytCnt < ui8Length ; ui8BytCnt++)
    {
    	*(pui8Dest+ui8BytCnt) = *(pui8DestTemp+ui8BytCnt);
    }
}