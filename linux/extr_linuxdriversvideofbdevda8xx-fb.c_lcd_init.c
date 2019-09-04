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
struct lcd_ctrl_config {int bpp; int fdd; int /*<<< orphan*/  raster_order; int /*<<< orphan*/  fifo_th; int /*<<< orphan*/  dma_burst_sz; } ;
struct fb_videomode {int sync; scalar_t__ yres; scalar_t__ xres; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  upper_margin; } ;
struct da8xx_fb_par {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FB_SYNC_CLK_INVERT ; 
 int LCD_INVERT_PIXEL_CLOCK ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int /*<<< orphan*/  LCD_RASTER_TIMING_2_REG ; 
 int da8xx_fb_calc_config_clk_divider (struct da8xx_fb_par*,struct fb_videomode*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lcd_cfg_display (struct lcd_ctrl_config const*,struct fb_videomode*) ; 
 int lcd_cfg_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lcd_cfg_frame_buffer (struct da8xx_fb_par*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_cfg_horizontal_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_cfg_vertical_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcd_init(struct da8xx_fb_par *par, const struct lcd_ctrl_config *cfg,
		struct fb_videomode *panel)
{
	u32 bpp;
	int ret = 0;

	ret = da8xx_fb_calc_config_clk_divider(par, panel);
	if (ret) {
		dev_err(par->dev, "unable to configure clock\n");
		return ret;
	}

	if (panel->sync & FB_SYNC_CLK_INVERT)
		lcdc_write((lcdc_read(LCD_RASTER_TIMING_2_REG) |
			LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);
	else
		lcdc_write((lcdc_read(LCD_RASTER_TIMING_2_REG) &
			~LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);

	/* Configure the DMA burst size and fifo threshold. */
	ret = lcd_cfg_dma(cfg->dma_burst_sz, cfg->fifo_th);
	if (ret < 0)
		return ret;

	/* Configure the vertical and horizontal sync properties. */
	lcd_cfg_vertical_sync(panel->upper_margin, panel->vsync_len,
			panel->lower_margin);
	lcd_cfg_horizontal_sync(panel->left_margin, panel->hsync_len,
			panel->right_margin);

	/* Configure for disply */
	ret = lcd_cfg_display(cfg, panel);
	if (ret < 0)
		return ret;

	bpp = cfg->bpp;

	if (bpp == 12)
		bpp = 16;
	ret = lcd_cfg_frame_buffer(par, (unsigned int)panel->xres,
				(unsigned int)panel->yres, bpp,
				cfg->raster_order);
	if (ret < 0)
		return ret;

	/* Configure FDD */
	lcdc_write((lcdc_read(LCD_RASTER_CTRL_REG) & 0xfff00fff) |
		       (cfg->fdd << 12), LCD_RASTER_CTRL_REG);

	return 0;
}