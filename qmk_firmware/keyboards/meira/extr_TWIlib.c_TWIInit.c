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
struct TYPE_2__ {int errorCode; scalar_t__ repStart; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int F_CPU ; 
 int /*<<< orphan*/  Ready ; 
 int TWBR ; 
 int TWCR ; 
 int TWEN ; 
 int TWIE ; 
 TYPE_1__ TWIInfo ; 
 int TWI_FREQ ; 
 scalar_t__ TWSR ; 

void TWIInit()
{
	TWIInfo.mode = Ready;
	TWIInfo.errorCode = 0xFF;
	TWIInfo.repStart = 0;
	// Set pre-scalers (no pre-scaling)
	TWSR = 0;
	// Set bit rate
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
	// Enable TWI and interrupt
	TWCR = (1 << TWIE) | (1 << TWEN);
}