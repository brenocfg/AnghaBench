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

/* Variables and functions */
 scalar_t__ RXBuffIndex ; 
 scalar_t__ RXBuffLen ; 
 scalar_t__ RXMAXBUFLEN ; 
 int /*<<< orphan*/  TWITransmitData (scalar_t__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

uint8_t TWIReadData(uint8_t TWIaddr, uint8_t bytesToRead, uint8_t repStart)
{
	// Check if number of bytes to read can fit in the RXbuffer
	if (bytesToRead < RXMAXBUFLEN)
	{
		// Reset buffer index and set RXBuffLen to the number of bytes to read
		RXBuffIndex = 0;
		RXBuffLen = bytesToRead;
		// Create the one value array for the address to be transmitted
		uint8_t TXdata[1];
		// Shift the address and AND a 1 into the read write bit (set to write mode)
		TXdata[0] = (TWIaddr << 1) | 0x01;
		// Use the TWITransmitData function to initialize the transfer and address the slave
		TWITransmitData(TXdata, 1, repStart, 0);
	}
	else
	{
		return 0;
	}
	return 1;
}