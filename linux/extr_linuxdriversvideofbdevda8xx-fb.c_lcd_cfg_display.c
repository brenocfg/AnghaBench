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
struct lcd_ctrl_config {int panel_shade; int bpp; scalar_t__ sync_edge; int /*<<< orphan*/  stn_565_mode; int /*<<< orphan*/  ac_bias_intrpt; int /*<<< orphan*/  ac_bias; int /*<<< orphan*/  tft_alt_mode; int /*<<< orphan*/  mono_8bit_mode; } ;
struct fb_videomode {int sync; } ;

/* Variables and functions */
#define  COLOR_ACTIVE 130 
#define  COLOR_PASSIVE 129 
 int EINVAL ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  LCD_INT_ENABLE_SET_REG ; 
 int LCD_INVERT_FRAME_CLOCK ; 
 int LCD_INVERT_LINE_CLOCK ; 
 int LCD_MONOCHROME_MODE ; 
 int LCD_MONO_8BIT_MODE ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int /*<<< orphan*/  LCD_RASTER_TIMING_2_REG ; 
 int LCD_STN_565_ENABLE ; 
 int LCD_SYNC_CTRL ; 
 int LCD_SYNC_EDGE ; 
 int LCD_TFT_ALT_ENABLE ; 
 int LCD_TFT_MODE ; 
 int LCD_V1_UNDERFLOW_INT_ENA ; 
 int LCD_V2_UNDERFLOW_INT_ENA ; 
 scalar_t__ LCD_VERSION_1 ; 
#define  MONOCHROME 128 
 int /*<<< orphan*/  lcd_cfg_ac_bias (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lcd_revision ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcd_cfg_display(const struct lcd_ctrl_config *cfg,
		struct fb_videomode *panel)
{
	u32 reg;
	u32 reg_int;

	reg = lcdc_read(LCD_RASTER_CTRL_REG) & ~(LCD_TFT_MODE |
						LCD_MONO_8BIT_MODE |
						LCD_MONOCHROME_MODE);

	switch (cfg->panel_shade) {
	case MONOCHROME:
		reg |= LCD_MONOCHROME_MODE;
		if (cfg->mono_8bit_mode)
			reg |= LCD_MONO_8BIT_MODE;
		break;
	case COLOR_ACTIVE:
		reg |= LCD_TFT_MODE;
		if (cfg->tft_alt_mode)
			reg |= LCD_TFT_ALT_ENABLE;
		break;

	case COLOR_PASSIVE:
		/* AC bias applicable only for Pasive panels */
		lcd_cfg_ac_bias(cfg->ac_bias, cfg->ac_bias_intrpt);
		if (cfg->bpp == 12 && cfg->stn_565_mode)
			reg |= LCD_STN_565_ENABLE;
		break;

	default:
		return -EINVAL;
	}

	/* enable additional interrupts here */
	if (lcd_revision == LCD_VERSION_1) {
		reg |= LCD_V1_UNDERFLOW_INT_ENA;
	} else {
		reg_int = lcdc_read(LCD_INT_ENABLE_SET_REG) |
			LCD_V2_UNDERFLOW_INT_ENA;
		lcdc_write(reg_int, LCD_INT_ENABLE_SET_REG);
	}

	lcdc_write(reg, LCD_RASTER_CTRL_REG);

	reg = lcdc_read(LCD_RASTER_TIMING_2_REG);

	reg |= LCD_SYNC_CTRL;

	if (cfg->sync_edge)
		reg |= LCD_SYNC_EDGE;
	else
		reg &= ~LCD_SYNC_EDGE;

	if ((panel->sync & FB_SYNC_HOR_HIGH_ACT) == 0)
		reg |= LCD_INVERT_LINE_CLOCK;
	else
		reg &= ~LCD_INVERT_LINE_CLOCK;

	if ((panel->sync & FB_SYNC_VERT_HIGH_ACT) == 0)
		reg |= LCD_INVERT_FRAME_CLOCK;
	else
		reg &= ~LCD_INVERT_FRAME_CLOCK;

	lcdc_write(reg, LCD_RASTER_TIMING_2_REG);

	return 0;
}