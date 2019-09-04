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
struct ocelot_pin_caps {unsigned int* functions; } ;
struct TYPE_2__ {struct ocelot_pin_caps* drv_data; } ;

/* Variables and functions */
 int OCELOT_FUNC_PER_PIN ; 
 TYPE_1__* ocelot_pins ; 

__attribute__((used)) static int ocelot_pin_function_idx(unsigned int pin, unsigned int function)
{
	struct ocelot_pin_caps *p = ocelot_pins[pin].drv_data;
	int i;

	for (i = 0; i < OCELOT_FUNC_PER_PIN; i++) {
		if (function == p->functions[i])
			return i;
	}

	return -1;
}