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
struct corgi_lcd {int gpio_backlight_cont_inverted; int intensity; int /*<<< orphan*/  (* kick_battery ) () ;int /*<<< orphan*/  gpio_backlight_on; int /*<<< orphan*/  gpio_backlight_cont; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUTYCTRL_ADRS ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (struct corgi_lcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int corgi_bl_set_intensity(struct corgi_lcd *lcd, int intensity)
{
	int cont;

	if (intensity > 0x10)
		intensity += 0x10;

	corgi_ssp_lcdtg_send(lcd, DUTYCTRL_ADRS, intensity);

	/* Bit 5 via GPIO_BACKLIGHT_CONT */
	cont = !!(intensity & 0x20) ^ lcd->gpio_backlight_cont_inverted;

	if (gpio_is_valid(lcd->gpio_backlight_cont))
		gpio_set_value_cansleep(lcd->gpio_backlight_cont, cont);

	if (gpio_is_valid(lcd->gpio_backlight_on))
		gpio_set_value_cansleep(lcd->gpio_backlight_on, intensity);

	if (lcd->kick_battery)
		lcd->kick_battery();

	lcd->intensity = intensity;
	return 0;
}