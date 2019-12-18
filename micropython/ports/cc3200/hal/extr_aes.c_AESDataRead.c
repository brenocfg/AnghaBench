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
 scalar_t__ AES_BASE ; 
 scalar_t__ AES_CTRL_OUTPUT_READY ; 
 scalar_t__ AES_O_CTRL ; 
 scalar_t__ AES_O_DATA_IN_0 ; 
 scalar_t__ AES_O_DATA_IN_1 ; 
 scalar_t__ AES_O_DATA_IN_2 ; 
 scalar_t__ AES_O_DATA_IN_3 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ HWREG (scalar_t__) ; 

void
AESDataRead(uint32_t ui32Base, uint8_t *pui8Dest, uint8_t ui8Length)
{
	volatile uint32_t pui32Dest[4];
	uint8_t ui8BytCnt;
	uint8_t *pui8DestTemp;

    //
    // Check the arguments.
    //
    ASSERT(ui32Base == AES_BASE);
    if((ui8Length == 0)||(ui8Length>16))
   	{
       	return;
    }


    //
    // Wait for the output to be ready before reading the data.
    //
    while((AES_CTRL_OUTPUT_READY & (HWREG(ui32Base + AES_O_CTRL))) == 0)
    {
    }

    //
    // Read a block of data from the data registers
    //
    pui32Dest[0] = HWREG(ui32Base + AES_O_DATA_IN_3);
    pui32Dest[1] = HWREG(ui32Base + AES_O_DATA_IN_2);
    pui32Dest[2] = HWREG(ui32Base + AES_O_DATA_IN_1);
    pui32Dest[3] = HWREG(ui32Base + AES_O_DATA_IN_0);
    //
    //Copy the data to a block memory
    //
    pui8DestTemp = (uint8_t *)pui32Dest;
    for(ui8BytCnt = 0; ui8BytCnt < ui8Length ; ui8BytCnt++)
   	{
    	*(pui8Dest+ui8BytCnt) = *(pui8DestTemp+ui8BytCnt);
   	}

    return;
}