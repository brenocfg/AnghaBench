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
typedef  size_t uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 int /*<<< orphan*/ ** intFunc ; 
 int* portConfigRegister (size_t) ; 

void detachInterrupt(uint8_t pin)
{
	volatile uint32_t *config;

	config = portConfigRegister(pin);
	__disable_irq();
	*config = ((*config & ~0x000F0000) | 0x01000000);
	intFunc[pin] = NULL;
	__enable_irq();
}