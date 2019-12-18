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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ CORE_NUM_DIGITAL ; 
 int volatile PORT_PCR_PE ; 
 int volatile PORT_PCR_PS ; 
 int* portClearRegister (scalar_t__) ; 
 int* portConfigRegister (scalar_t__) ; 
 scalar_t__* portModeRegister (scalar_t__) ; 
 int* portSetRegister (scalar_t__) ; 

void digitalWrite(uint8_t pin, uint8_t val)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	if (*portModeRegister(pin)) {
		if (val) {
			*portSetRegister(pin) = 1;
		} else {
			*portClearRegister(pin) = 1;
		}
	} else {
		volatile uint32_t *config = portConfigRegister(pin);
		if (val) {
			// TODO use bitband for atomic read-mod-write
			*config |= (PORT_PCR_PE | PORT_PCR_PS);
			//*config = PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS;
		} else {
			// TODO use bitband for atomic read-mod-write
			*config &= ~(PORT_PCR_PE);
			//*config = PORT_PCR_MUX(1);
		}
	}

}