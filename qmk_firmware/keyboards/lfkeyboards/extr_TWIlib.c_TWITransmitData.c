#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_2__ {scalar_t__ mode; void* repStart; } ;

/* Variables and functions */
 void* Initializing ; 
 scalar_t__ RepeatedStartSent ; 
 int TWCR ; 
 void* TWDR ; 
 TYPE_1__ TWIInfo ; 
 int /*<<< orphan*/  TWIInit () ; 
 int TWINT ; 
 int /*<<< orphan*/  TWISendStart () ; 
 int /*<<< orphan*/  TWISendTransmit () ; 
 void** TWITransmitBuffer ; 
 int TWSTO ; 
 scalar_t__ TXBuffIndex ; 
 void* TXBuffLen ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  isTWIReady () ; 

void TWITransmitData(void *const TXdata, uint8_t dataLen, uint8_t repStart, uint8_t blocking)
{
	// Wait until ready
	while (!isTWIReady()) {_delay_us(1);}
	// Reset the I2C stuff
	TWCR = (1 << TWINT)|(1 << TWSTO);
	TWIInit();
	// Set repeated start mode
	TWIInfo.repStart = repStart;
	// Copy transmit info to global variables
	TWITransmitBuffer = (uint8_t *)TXdata;
	TXBuffLen = dataLen;
	TXBuffIndex = 0;

	// If a repeated start has been sent, then devices are already listening for an address
	// and another start does not need to be sent.
	if (TWIInfo.mode == RepeatedStartSent)
	{
		TWIInfo.mode = Initializing;
		TWDR = TWITransmitBuffer[TXBuffIndex++]; // Load data to transmit buffer
		TWISendTransmit(); // Send the data
	}
	else // Otherwise, just send the normal start signal to begin transmission.
	{
		TWIInfo.mode = Initializing;
		TWISendStart();
	}
	if(blocking){
		// Wait until ready
		while (!isTWIReady()){_delay_us(1);}
	}
}