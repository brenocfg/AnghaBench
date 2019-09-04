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
struct lcd_device {int dummy; } ;
struct ili922x {int power; } ;

/* Variables and functions */
 struct ili922x* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int ili922x_get_power(struct lcd_device *ld)
{
	struct ili922x *ili = lcd_get_data(ld);

	return ili->power;
}