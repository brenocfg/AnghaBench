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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ CORE_NUM_DIGITAL ; 
 int /*<<< orphan*/  portInputRegister (scalar_t__) ; 
 int /*<<< orphan*/  pulseIn_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulseIn_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout)
{
	if (pin >= CORE_NUM_DIGITAL) return 0;
	if (state) return pulseIn_high(portInputRegister(pin), timeout);
	return pulseIn_low(portInputRegister(pin), timeout);;
}