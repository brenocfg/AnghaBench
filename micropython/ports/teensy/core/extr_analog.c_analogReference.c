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
 scalar_t__ ADC0_SC3 ; 
 scalar_t__ ADC1_SC3 ; 
 int /*<<< orphan*/  analog_init () ; 
 int analog_reference_internal ; 
 scalar_t__ calibrating ; 

void analogReference(uint8_t type)
{
	if (type) {
		// internal reference requested
		if (!analog_reference_internal) {
			analog_reference_internal = 1;
			if (calibrating) {
				ADC0_SC3 = 0; // cancel cal
#if defined(__MK20DX256__)
				ADC1_SC3 = 0; // cancel cal
#endif
			}
			analog_init();
		}
	} else {
		// vcc or external reference requested
		if (analog_reference_internal) {
			analog_reference_internal = 0;
			if (calibrating) {
				ADC0_SC3 = 0; // cancel cal
#if defined(__MK20DX256__)
				ADC1_SC3 = 0; // cancel cal
#endif
			}
			analog_init();
		}
	}
}