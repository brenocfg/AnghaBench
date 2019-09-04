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

/* Variables and functions */
 int GP_CLIENTSEL (int) ; 
 int PINS_PER_COLLECTION ; 

__attribute__((used)) static void dc_client_sel(int pin_num, int *reg, int *bit)
{
	*bit = (pin_num % PINS_PER_COLLECTION) * 2;
	*reg = GP_CLIENTSEL(pin_num/PINS_PER_COLLECTION);

	if (*bit >= PINS_PER_COLLECTION) {
		*bit -= PINS_PER_COLLECTION;
		*reg += 1;
	}
}