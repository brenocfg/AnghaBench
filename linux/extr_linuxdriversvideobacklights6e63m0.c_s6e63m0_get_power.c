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
struct s6e63m0 {int power; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 struct s6e63m0* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int s6e63m0_get_power(struct lcd_device *ld)
{
	struct s6e63m0 *lcd = lcd_get_data(ld);

	return lcd->power;
}