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
typedef  int /*<<< orphan*/  u_int ;
struct au1200_lcd_global_regs_t {int flags; int brightness; int /*<<< orphan*/  mask; int /*<<< orphan*/  colorkey; int /*<<< orphan*/  backcolor; } ;
struct TYPE_2__ {int pwmdiv; int pwmhi; int /*<<< orphan*/  colorkeymsk; int /*<<< orphan*/  colorkey; int /*<<< orphan*/  backcolor; } ;

/* Variables and functions */
 int SCREEN_BACKCOLOR ; 
 int SCREEN_BRIGHTNESS ; 
 int SCREEN_COLORKEY ; 
 int SCREEN_MASK ; 
 TYPE_1__* lcd ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void set_global(u_int cmd, struct au1200_lcd_global_regs_t *pdata)
{

	unsigned int hi1, divider;

	/* SCREEN_SIZE: user cannot reset size, must switch panel choice */

	if (pdata->flags & SCREEN_BACKCOLOR)
		lcd->backcolor = pdata->backcolor;

	if (pdata->flags & SCREEN_BRIGHTNESS) {

		// limit brightness pwm duty to >= 30/1600
		if (pdata->brightness < 30) {
			pdata->brightness = 30;
		}
		divider = (lcd->pwmdiv & 0x3FFFF) + 1;
		hi1 = (((pdata->brightness & 0xFF)+1) * divider >> 8);
		lcd->pwmhi &= 0xFFFF;
		lcd->pwmhi |= (hi1 << 16);
	}

	if (pdata->flags & SCREEN_COLORKEY)
		lcd->colorkey = pdata->colorkey;

	if (pdata->flags & SCREEN_MASK)
		lcd->colorkeymsk = pdata->mask;
	wmb(); /* drain writebuffer */
}