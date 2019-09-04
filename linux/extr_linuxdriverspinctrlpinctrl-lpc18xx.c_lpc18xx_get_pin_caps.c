#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpc18xx_pin_caps {int dummy; } ;
struct TYPE_3__ {unsigned int number; struct lpc18xx_pin_caps* drv_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* lpc18xx_pins ; 

__attribute__((used)) static struct lpc18xx_pin_caps *lpc18xx_get_pin_caps(unsigned pin)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(lpc18xx_pins); i++) {
		if (lpc18xx_pins[i].number == pin)
			return lpc18xx_pins[i].drv_data;
	}

	return NULL;
}