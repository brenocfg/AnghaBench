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
typedef  int u32 ;

/* Variables and functions */
 int LCD_CLK_MAIN_RESET ; 
 int /*<<< orphan*/  LCD_CLK_RESET_REG ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int LCD_RASTER_ENABLE ; 
 scalar_t__ LCD_VERSION_2 ; 
 scalar_t__ lcd_revision ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void lcd_enable_raster(void)
{
	u32 reg;

	/* Put LCDC in reset for several cycles */
	if (lcd_revision == LCD_VERSION_2)
		/* Write 1 to reset LCDC */
		lcdc_write(LCD_CLK_MAIN_RESET, LCD_CLK_RESET_REG);
	mdelay(1);

	/* Bring LCDC out of reset */
	if (lcd_revision == LCD_VERSION_2)
		lcdc_write(0, LCD_CLK_RESET_REG);
	mdelay(1);

	/* Above reset sequence doesnot reset register context */
	reg = lcdc_read(LCD_RASTER_CTRL_REG);
	if (!(reg & LCD_RASTER_ENABLE))
		lcdc_write(reg | LCD_RASTER_ENABLE, LCD_RASTER_CTRL_REG);
}