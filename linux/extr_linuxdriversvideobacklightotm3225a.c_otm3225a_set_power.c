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
struct otm3225a_data {int power; int /*<<< orphan*/  spi; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  display_off ; 
 int /*<<< orphan*/  display_on ; 
 struct otm3225a_data* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  otm3225a_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otm3225a_set_power(struct lcd_device *ld, int power)
{
	struct otm3225a_data *dd = lcd_get_data(ld);

	if (power == dd->power)
		return 0;

	if (power > FB_BLANK_UNBLANK)
		otm3225a_write(dd->spi, display_off, ARRAY_SIZE(display_off));
	else
		otm3225a_write(dd->spi, display_on, ARRAY_SIZE(display_on));
	dd->power = power;

	return 0;
}