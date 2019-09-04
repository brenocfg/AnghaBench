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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_LCD_BRIGHTNESS ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  HD64461_GPBDR ; 
 int /*<<< orphan*/  HD64461_GPBDR_LCDOFF ; 
 int /*<<< orphan*/  bl_lock ; 
 int current_intensity ; 
 scalar_t__ hp680bl_suspended ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dac_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dac_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dac_output (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hp680bl_send_intensity(struct backlight_device *bd)
{
	unsigned long flags;
	u16 v;
	int intensity = bd->props.brightness;

	if (bd->props.power != FB_BLANK_UNBLANK)
		intensity = 0;
	if (bd->props.fb_blank != FB_BLANK_UNBLANK)
		intensity = 0;
	if (hp680bl_suspended)
		intensity = 0;

	spin_lock_irqsave(&bl_lock, flags);
	if (intensity && current_intensity == 0) {
		sh_dac_enable(DAC_LCD_BRIGHTNESS);
		v = inw(HD64461_GPBDR);
		v &= ~HD64461_GPBDR_LCDOFF;
		outw(v, HD64461_GPBDR);
		sh_dac_output(255-(u8)intensity, DAC_LCD_BRIGHTNESS);
	} else if (intensity == 0 && current_intensity != 0) {
		sh_dac_output(255-(u8)intensity, DAC_LCD_BRIGHTNESS);
		sh_dac_disable(DAC_LCD_BRIGHTNESS);
		v = inw(HD64461_GPBDR);
		v |= HD64461_GPBDR_LCDOFF;
		outw(v, HD64461_GPBDR);
	} else if (intensity) {
		sh_dac_output(255-(u8)intensity, DAC_LCD_BRIGHTNESS);
	}
	spin_unlock_irqrestore(&bl_lock, flags);

	current_intensity = intensity;
}