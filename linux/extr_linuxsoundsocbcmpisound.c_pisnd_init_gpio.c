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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_ASIS ; 
 void* button ; 
 int /*<<< orphan*/  gpiod_direction_output (void*,int) ; 
 int /*<<< orphan*/  gpiod_export (void*,int) ; 
 void* gpiod_get_index (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (void*,int) ; 
 void* osr0 ; 
 void* osr1 ; 
 void* osr2 ; 
 void* reset ; 

__attribute__((used)) static int pisnd_init_gpio(struct device *dev)
{
	osr0 = gpiod_get_index(dev, "osr", 0, GPIOD_ASIS);
	osr1 = gpiod_get_index(dev, "osr", 1, GPIOD_ASIS);
	osr2 = gpiod_get_index(dev, "osr", 2, GPIOD_ASIS);

	reset = gpiod_get_index(dev, "reset", 0, GPIOD_ASIS);

	button = gpiod_get_index(dev, "button", 0, GPIOD_ASIS);

	gpiod_direction_output(osr0,  1);
	gpiod_direction_output(osr1,  1);
	gpiod_direction_output(osr2,  1);
	gpiod_direction_output(reset, 1);

	gpiod_set_value(reset, false);
	gpiod_set_value(osr0,   true);
	gpiod_set_value(osr1,  false);
	gpiod_set_value(osr2,  false);
	gpiod_set_value(reset,  true);

	gpiod_export(button, false);

	return 0;
}