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
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int LCD_ADV_PROG_CTRL ; 
 int LCD_ADV_PROG_CTRL2 ; 
 int LCD_ALL_PIXEL ; 
 int LCD_BIAS ; 
 int LCD_BOTTOMVIEW ; 
 int LCD_DISPLAY_ENABLE ; 
 int LCD_DISPLAY_INVERT ; 
 int LCD_NO_OP ; 
 int LCD_POWER_CONTROL ; 
 int LCD_RESET_CMD ; 
 int LCD_SCAN_DIR ; 
 int LCD_START_LINE ; 
 int LCD_TEMPCOMP_HIGH ; 
 int LCD_VOLTAGE ; 
 int LCD_VOLUME_MODE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	/* softreset of LCD */
	write_reg(par, LCD_RESET_CMD);
	mdelay(10);

	/* set startpoint */
	write_reg(par, LCD_START_LINE);

	/* select orientation BOTTOMVIEW */
	write_reg(par, LCD_BOTTOMVIEW | 1);

	/* output mode select (turns display upside-down) */
	write_reg(par, LCD_SCAN_DIR | 0x00);

	/* Normal Pixel mode */
	write_reg(par, LCD_ALL_PIXEL | 0);

	/* positive display */
	write_reg(par, LCD_DISPLAY_INVERT | 0);

	/* bias 1/9 */
	write_reg(par, LCD_BIAS | 0);

	/* power control mode: all features on */
	write_reg(par, LCD_POWER_CONTROL | 0x07);

	/* set voltage regulator R/R */
	write_reg(par, LCD_VOLTAGE | 0x07);

	/* volume mode set */
	write_reg(par, LCD_VOLUME_MODE);
	write_reg(par, 0x09);
	write_reg(par, LCD_NO_OP);

	/* advanced program control */
	write_reg(par, LCD_ADV_PROG_CTRL);
	write_reg(par, LCD_ADV_PROG_CTRL2 | LCD_TEMPCOMP_HIGH);

	/* enable display */
	write_reg(par, LCD_DISPLAY_ENABLE | 1);

	return 0;
}