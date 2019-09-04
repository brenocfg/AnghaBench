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
typedef  unsigned long uint32_t ;
typedef  unsigned long uint16_t ;
struct jzfb {int /*<<< orphan*/  ldclk; int /*<<< orphan*/  lpclk; int /*<<< orphan*/  lock; int /*<<< orphan*/  is_enabled; scalar_t__ base; struct jz4740_fb_platform_data* pdata; } ;
struct TYPE_2__ {unsigned long spl; unsigned long cls; unsigned long ps; } ;
struct jz4740_fb_platform_data {int bpp; int lcd_type; TYPE_1__ special_tft_config; scalar_t__ date_enable_active_low; scalar_t__ pixclk_falling_edge; } ;
struct fb_videomode {unsigned long hsync_len; unsigned long left_margin; unsigned long xres; unsigned long right_margin; unsigned long vsync_len; unsigned long upper_margin; unsigned long yres; unsigned long lower_margin; int sync; unsigned long refresh; scalar_t__ pixclock; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {struct fb_videomode* mode; struct fb_var_screeninfo var; struct jzfb* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 unsigned long JZ_LCD_CFG_18_BIT ; 
 unsigned long JZ_LCD_CFG_CLS_DISABLE ; 
 unsigned long JZ_LCD_CFG_DE_ACTIVE_LOW ; 
 unsigned long JZ_LCD_CFG_HSYNC_ACTIVE_LOW ; 
 unsigned long JZ_LCD_CFG_PCLK_FALLING_EDGE ; 
 unsigned long JZ_LCD_CFG_PS_DISABLE ; 
 unsigned long JZ_LCD_CFG_REV_DISABLE ; 
 unsigned long JZ_LCD_CFG_SPL_DISABLE ; 
 unsigned long JZ_LCD_CFG_VSYNC_ACTIVE_LOW ; 
 unsigned long JZ_LCD_CTRL_BPP_1 ; 
 unsigned long JZ_LCD_CTRL_BPP_15_16 ; 
 unsigned long JZ_LCD_CTRL_BPP_18_24 ; 
 unsigned long JZ_LCD_CTRL_BPP_2 ; 
 unsigned long JZ_LCD_CTRL_BPP_4 ; 
 unsigned long JZ_LCD_CTRL_BPP_8 ; 
 unsigned long JZ_LCD_CTRL_BURST_16 ; 
 unsigned long JZ_LCD_CTRL_ENABLE ; 
 unsigned long JZ_LCD_CTRL_OFUP ; 
 unsigned long JZ_LCD_CTRL_RGB555 ; 
 int JZ_LCD_TYPE_8BIT_SERIAL ; 
 int JZ_LCD_TYPE_GENERIC_18_BIT ; 
#define  JZ_LCD_TYPE_SPECIAL_TFT_1 130 
#define  JZ_LCD_TYPE_SPECIAL_TFT_2 129 
#define  JZ_LCD_TYPE_SPECIAL_TFT_3 128 
 scalar_t__ JZ_REG_LCD_CFG ; 
 scalar_t__ JZ_REG_LCD_CLS ; 
 scalar_t__ JZ_REG_LCD_CTRL ; 
 scalar_t__ JZ_REG_LCD_DAH ; 
 scalar_t__ JZ_REG_LCD_DAV ; 
 scalar_t__ JZ_REG_LCD_HSYNC ; 
 scalar_t__ JZ_REG_LCD_PS ; 
 scalar_t__ JZ_REG_LCD_REV ; 
 scalar_t__ JZ_REG_LCD_SPL ; 
 scalar_t__ JZ_REG_LCD_VAT ; 
 scalar_t__ JZ_REG_LCD_VSYNC ; 
 scalar_t__ KHZ2PICOS (unsigned long) ; 
 int PICOS2KHZ (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct fb_videomode* jzfb_get_mode (struct jzfb*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int jzfb_set_par(struct fb_info *info)
{
	struct jzfb *jzfb = info->par;
	struct jz4740_fb_platform_data *pdata = jzfb->pdata;
	struct fb_var_screeninfo *var = &info->var;
	struct fb_videomode *mode;
	uint16_t hds, vds;
	uint16_t hde, vde;
	uint16_t ht, vt;
	uint32_t ctrl;
	uint32_t cfg;
	unsigned long rate;

	mode = jzfb_get_mode(jzfb, var);
	if (mode == NULL)
		return -EINVAL;

	if (mode == info->mode)
		return 0;

	info->mode = mode;

	hds = mode->hsync_len + mode->left_margin;
	hde = hds + mode->xres;
	ht = hde + mode->right_margin;

	vds = mode->vsync_len + mode->upper_margin;
	vde = vds + mode->yres;
	vt = vde + mode->lower_margin;

	ctrl = JZ_LCD_CTRL_OFUP | JZ_LCD_CTRL_BURST_16;

	switch (pdata->bpp) {
	case 1:
		ctrl |= JZ_LCD_CTRL_BPP_1;
		break;
	case 2:
		ctrl |= JZ_LCD_CTRL_BPP_2;
		break;
	case 4:
		ctrl |= JZ_LCD_CTRL_BPP_4;
		break;
	case 8:
		ctrl |= JZ_LCD_CTRL_BPP_8;
	break;
	case 15:
		ctrl |= JZ_LCD_CTRL_RGB555; /* Falltrough */
	case 16:
		ctrl |= JZ_LCD_CTRL_BPP_15_16;
		break;
	case 18:
	case 24:
	case 32:
		ctrl |= JZ_LCD_CTRL_BPP_18_24;
		break;
	default:
		break;
	}

	cfg = pdata->lcd_type & 0xf;

	if (!(mode->sync & FB_SYNC_HOR_HIGH_ACT))
		cfg |= JZ_LCD_CFG_HSYNC_ACTIVE_LOW;

	if (!(mode->sync & FB_SYNC_VERT_HIGH_ACT))
		cfg |= JZ_LCD_CFG_VSYNC_ACTIVE_LOW;

	if (pdata->pixclk_falling_edge)
		cfg |= JZ_LCD_CFG_PCLK_FALLING_EDGE;

	if (pdata->date_enable_active_low)
		cfg |= JZ_LCD_CFG_DE_ACTIVE_LOW;

	if (pdata->lcd_type == JZ_LCD_TYPE_GENERIC_18_BIT)
		cfg |= JZ_LCD_CFG_18_BIT;

	if (mode->pixclock) {
		rate = PICOS2KHZ(mode->pixclock) * 1000;
		mode->refresh = rate / vt / ht;
	} else {
		if (pdata->lcd_type == JZ_LCD_TYPE_8BIT_SERIAL)
			rate = mode->refresh * (vt + 2 * mode->xres) * ht;
		else
			rate = mode->refresh * vt * ht;

		mode->pixclock = KHZ2PICOS(rate / 1000);
	}

	mutex_lock(&jzfb->lock);
	if (!jzfb->is_enabled)
		clk_enable(jzfb->ldclk);
	else
		ctrl |= JZ_LCD_CTRL_ENABLE;

	switch (pdata->lcd_type) {
	case JZ_LCD_TYPE_SPECIAL_TFT_1:
	case JZ_LCD_TYPE_SPECIAL_TFT_2:
	case JZ_LCD_TYPE_SPECIAL_TFT_3:
		writel(pdata->special_tft_config.spl, jzfb->base + JZ_REG_LCD_SPL);
		writel(pdata->special_tft_config.cls, jzfb->base + JZ_REG_LCD_CLS);
		writel(pdata->special_tft_config.ps, jzfb->base + JZ_REG_LCD_PS);
		writel(pdata->special_tft_config.ps, jzfb->base + JZ_REG_LCD_REV);
		break;
	default:
		cfg |= JZ_LCD_CFG_PS_DISABLE;
		cfg |= JZ_LCD_CFG_CLS_DISABLE;
		cfg |= JZ_LCD_CFG_SPL_DISABLE;
		cfg |= JZ_LCD_CFG_REV_DISABLE;
		break;
	}

	writel(mode->hsync_len, jzfb->base + JZ_REG_LCD_HSYNC);
	writel(mode->vsync_len, jzfb->base + JZ_REG_LCD_VSYNC);

	writel((ht << 16) | vt, jzfb->base + JZ_REG_LCD_VAT);

	writel((hds << 16) | hde, jzfb->base + JZ_REG_LCD_DAH);
	writel((vds << 16) | vde, jzfb->base + JZ_REG_LCD_DAV);

	writel(cfg, jzfb->base + JZ_REG_LCD_CFG);

	writel(ctrl, jzfb->base + JZ_REG_LCD_CTRL);

	if (!jzfb->is_enabled)
		clk_disable_unprepare(jzfb->ldclk);

	mutex_unlock(&jzfb->lock);

	clk_set_rate(jzfb->lpclk, rate);
	clk_set_rate(jzfb->ldclk, rate * 3);

	return 0;
}