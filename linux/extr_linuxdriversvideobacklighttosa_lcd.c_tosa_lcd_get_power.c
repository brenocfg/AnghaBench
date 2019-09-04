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
struct tosa_lcd_data {int lcd_power; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 struct tosa_lcd_data* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int tosa_lcd_get_power(struct lcd_device *lcd)
{
	struct tosa_lcd_data *data = lcd_get_data(lcd);

	return data->lcd_power;
}