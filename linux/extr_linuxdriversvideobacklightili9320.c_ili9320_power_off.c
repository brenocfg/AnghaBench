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
struct ili9320 {int display1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILI9320_DISPLAY1 ; 
 int ILI9320_DISPLAY1_BASEE ; 
 int ILI9320_DISPLAY1_D (int) ; 
 int /*<<< orphan*/  ili9320_write (struct ili9320*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ili9320_power_off(struct ili9320 *lcd)
{
	lcd->display1 &= ~(ILI9320_DISPLAY1_D(3) | ILI9320_DISPLAY1_BASEE);
	ili9320_write(lcd, ILI9320_DISPLAY1, lcd->display1);

	return 0;
}