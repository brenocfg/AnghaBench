#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct au1200_lcd_window_regs_t {int flags; int xpos; int ypos; int alpha_color; int alpha_mode; int priority; int channel; int buffer_format; int color_order; int pixel_order; int xsize; int ysize; int colorkey_mode; int double_buffer_mode; int ram_array_mode; int enable; } ;
struct TYPE_4__ {unsigned int winenable; TYPE_1__* window; } ;
struct TYPE_3__ {int winctrl0; int winctrl1; unsigned int winctrl2; } ;

/* Variables and functions */
 int LCD_WINCTRL0_A ; 
 int LCD_WINCTRL0_AEN ; 
 int LCD_WINCTRL0_OX ; 
 int LCD_WINCTRL0_OY ; 
 int LCD_WINCTRL1_CCO ; 
 int LCD_WINCTRL1_FRM ; 
 int LCD_WINCTRL1_PIPE ; 
 int LCD_WINCTRL1_PO ; 
 int LCD_WINCTRL1_PRI ; 
 int LCD_WINCTRL1_SZX ; 
 int LCD_WINCTRL1_SZY ; 
 unsigned int LCD_WINCTRL2_BX ; 
 int LCD_WINCTRL2_CKMODE ; 
 int LCD_WINCTRL2_DBM ; 
 int LCD_WINCTRL2_RAM ; 
 int LCD_WINCTRL2_SCX ; 
 int LCD_WINCTRL2_SCY ; 
 int WIN_ALPHA_COLOR ; 
 int WIN_ALPHA_MODE ; 
 int WIN_BUFFER_FORMAT ; 
 int WIN_BUFFER_SCALE ; 
 int WIN_CHANNEL ; 
 int WIN_COLORKEY_MODE ; 
 int WIN_COLOR_ORDER ; 
 int WIN_DOUBLE_BUFFER_MODE ; 
 int WIN_ENABLE ; 
 int WIN_PIXEL_ORDER ; 
 int WIN_POSITION ; 
 int WIN_PRIORITY ; 
 int WIN_RAM_ARRAY_MODE ; 
 int WIN_SIZE ; 
 TYPE_2__* lcd ; 
 int winbpp (unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void set_window(unsigned int plane,
	struct au1200_lcd_window_regs_t *pdata)
{
	unsigned int val, bpp;

	/* Window control register 0 */
	if (pdata->flags & WIN_POSITION) {
		val = lcd->window[plane].winctrl0 & ~(LCD_WINCTRL0_OX |
				LCD_WINCTRL0_OY);
		val |= ((pdata->xpos << 21) & LCD_WINCTRL0_OX);
		val |= ((pdata->ypos << 10) & LCD_WINCTRL0_OY);
		lcd->window[plane].winctrl0 = val;
	}
	if (pdata->flags & WIN_ALPHA_COLOR) {
		val = lcd->window[plane].winctrl0 & ~(LCD_WINCTRL0_A);
		val |= ((pdata->alpha_color << 2) & LCD_WINCTRL0_A);
		lcd->window[plane].winctrl0 = val;
	}
	if (pdata->flags & WIN_ALPHA_MODE) {
		val = lcd->window[plane].winctrl0 & ~(LCD_WINCTRL0_AEN);
		val |= ((pdata->alpha_mode << 1) & LCD_WINCTRL0_AEN);
		lcd->window[plane].winctrl0 = val;
	}

	/* Window control register 1 */
	if (pdata->flags & WIN_PRIORITY) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_PRI);
		val |= ((pdata->priority << 30) & LCD_WINCTRL1_PRI);
		lcd->window[plane].winctrl1 = val;
	}
	if (pdata->flags & WIN_CHANNEL) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_PIPE);
		val |= ((pdata->channel << 29) & LCD_WINCTRL1_PIPE);
		lcd->window[plane].winctrl1 = val;
	}
	if (pdata->flags & WIN_BUFFER_FORMAT) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_FRM);
		val |= ((pdata->buffer_format << 25) & LCD_WINCTRL1_FRM);
		lcd->window[plane].winctrl1 = val;
	}
	if (pdata->flags & WIN_COLOR_ORDER) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_CCO);
		val |= ((pdata->color_order << 24) & LCD_WINCTRL1_CCO);
		lcd->window[plane].winctrl1 = val;
	}
	if (pdata->flags & WIN_PIXEL_ORDER) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_PO);
		val |= ((pdata->pixel_order << 22) & LCD_WINCTRL1_PO);
		lcd->window[plane].winctrl1 = val;
	}
	if (pdata->flags & WIN_SIZE) {
		val = lcd->window[plane].winctrl1 & ~(LCD_WINCTRL1_SZX |
				LCD_WINCTRL1_SZY);
		val |= (((pdata->xsize << 11) - 1) & LCD_WINCTRL1_SZX);
		val |= (((pdata->ysize) - 1) & LCD_WINCTRL1_SZY);
		lcd->window[plane].winctrl1 = val;
		/* program buffer line width */
		bpp = winbpp(val) / 8;
		val = lcd->window[plane].winctrl2 & ~(LCD_WINCTRL2_BX);
		val |= (((pdata->xsize * bpp) << 8) & LCD_WINCTRL2_BX);
		lcd->window[plane].winctrl2 = val;
	}

	/* Window control register 2 */
	if (pdata->flags & WIN_COLORKEY_MODE) {
		val = lcd->window[plane].winctrl2 & ~(LCD_WINCTRL2_CKMODE);
		val |= ((pdata->colorkey_mode << 24) & LCD_WINCTRL2_CKMODE);
		lcd->window[plane].winctrl2 = val;
	}
	if (pdata->flags & WIN_DOUBLE_BUFFER_MODE) {
		val = lcd->window[plane].winctrl2 & ~(LCD_WINCTRL2_DBM);
		val |= ((pdata->double_buffer_mode << 23) & LCD_WINCTRL2_DBM);
		lcd->window[plane].winctrl2 = val;
	}
	if (pdata->flags & WIN_RAM_ARRAY_MODE) {
		val = lcd->window[plane].winctrl2 & ~(LCD_WINCTRL2_RAM);
		val |= ((pdata->ram_array_mode << 21) & LCD_WINCTRL2_RAM);
		lcd->window[plane].winctrl2 = val;
	}

	/* Buffer line width programmed with WIN_SIZE */

	if (pdata->flags & WIN_BUFFER_SCALE) {
		val = lcd->window[plane].winctrl2 & ~(LCD_WINCTRL2_SCX |
				LCD_WINCTRL2_SCY);
		val |= ((pdata->xsize << 11) & LCD_WINCTRL2_SCX);
		val |= ((pdata->ysize) & LCD_WINCTRL2_SCY);
		lcd->window[plane].winctrl2 = val;
	}

	if (pdata->flags & WIN_ENABLE) {
		val = lcd->winenable;
		val &= ~(1<<plane);
		val |= (pdata->enable & 1) << plane;
		lcd->winenable = val;
	}
	wmb(); /* drain writebuffer */
}