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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct mx3fb_data {int h_start_width; int v_start_width; size_t disp_data_fmt; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct ipu_di_signal_cfg {int datamask_en; int clksel_en; int clkidle_en; int data_pol; int clk_pol; int enable_pol; int Hsync_pol; int Vsync_pol; } ;
struct di_mapping {int b0; int b1; int b2; } ;
struct clk {int dummy; } ;
typedef  enum ipu_panel { ____Placeholder_ipu_panel } ipu_panel ;

/* Variables and functions */
 int DI_D3_CLK_IDLE_SHIFT ; 
 int DI_D3_CLK_POL_SHIFT ; 
 int DI_D3_CLK_SEL_SHIFT ; 
 int DI_D3_DATAMSK_SHIFT ; 
 int DI_D3_DATA_POL_SHIFT ; 
 int DI_D3_DRDY_SHARP_POL_SHIFT ; 
 int DI_D3_HSYNC_POL_SHIFT ; 
 int DI_D3_VSYNC_POL_SHIFT ; 
 int /*<<< orphan*/  DI_DISP3_B0_MAP ; 
 int /*<<< orphan*/  DI_DISP3_B1_MAP ; 
 int /*<<< orphan*/  DI_DISP3_B2_MAP ; 
 int /*<<< orphan*/  DI_DISP3_TIME_CONF ; 
 int /*<<< orphan*/  DI_DISP_IF_CONF ; 
 int /*<<< orphan*/  DI_DISP_SIG_POL ; 
 int EINVAL ; 
#define  IPU_PANEL_SHARP_TFT 129 
#define  IPU_PANEL_TFT 128 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SDC_COM_CONF ; 
 int SDC_COM_SHARP ; 
 int SDC_COM_TFT_COLOR ; 
 int /*<<< orphan*/  SDC_HOR_CONF ; 
 int /*<<< orphan*/  SDC_SHARP_CONF_1 ; 
 int /*<<< orphan*/  SDC_SHARP_CONF_2 ; 
 int /*<<< orphan*/  SDC_VER_CONF ; 
 int SDC_V_SYNC_WIDTH_L ; 
 struct clk* clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct di_mapping* di_mappings ; 
 int mx3fb_read_reg (struct mx3fb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx3fb_write_reg (struct mx3fb_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sdc_init_panel(struct mx3fb_data *mx3fb, enum ipu_panel panel,
			  uint32_t pixel_clk,
			  uint16_t width, uint16_t height,
			  uint16_t h_start_width, uint16_t h_sync_width,
			  uint16_t h_end_width, uint16_t v_start_width,
			  uint16_t v_sync_width, uint16_t v_end_width,
			  struct ipu_di_signal_cfg sig)
{
	unsigned long lock_flags;
	uint32_t reg;
	uint32_t old_conf;
	uint32_t div;
	struct clk *ipu_clk;
	const struct di_mapping *map;

	dev_dbg(mx3fb->dev, "panel size = %d x %d", width, height);

	if (v_sync_width == 0 || h_sync_width == 0)
		return -EINVAL;

	/* Init panel size and blanking periods */
	reg = ((uint32_t) (h_sync_width - 1) << 26) |
		((uint32_t) (width + h_start_width + h_end_width - 1) << 16);
	mx3fb_write_reg(mx3fb, reg, SDC_HOR_CONF);

#ifdef DEBUG
	printk(KERN_CONT " hor_conf %x,", reg);
#endif

	reg = ((uint32_t) (v_sync_width - 1) << 26) | SDC_V_SYNC_WIDTH_L |
	    ((uint32_t) (height + v_start_width + v_end_width - 1) << 16);
	mx3fb_write_reg(mx3fb, reg, SDC_VER_CONF);

#ifdef DEBUG
	printk(KERN_CONT " ver_conf %x\n", reg);
#endif

	mx3fb->h_start_width = h_start_width;
	mx3fb->v_start_width = v_start_width;

	switch (panel) {
	case IPU_PANEL_SHARP_TFT:
		mx3fb_write_reg(mx3fb, 0x00FD0102L, SDC_SHARP_CONF_1);
		mx3fb_write_reg(mx3fb, 0x00F500F4L, SDC_SHARP_CONF_2);
		mx3fb_write_reg(mx3fb, SDC_COM_SHARP | SDC_COM_TFT_COLOR, SDC_COM_CONF);
		break;
	case IPU_PANEL_TFT:
		mx3fb_write_reg(mx3fb, SDC_COM_TFT_COLOR, SDC_COM_CONF);
		break;
	default:
		return -EINVAL;
	}

	/* Init clocking */

	/*
	 * Calculate divider: fractional part is 4 bits so simply multiple by
	 * 2^4 to get fractional part, as long as we stay under ~250MHz and on
	 * i.MX31 it (HSP_CLK) is <= 178MHz. Currently 128.267MHz
	 */
	ipu_clk = clk_get(mx3fb->dev, NULL);
	if (!IS_ERR(ipu_clk)) {
		div = clk_get_rate(ipu_clk) * 16 / pixel_clk;
		clk_put(ipu_clk);
	} else {
		div = 0;
	}

	if (div < 0x40) {	/* Divider less than 4 */
		dev_dbg(mx3fb->dev,
			"InitPanel() - Pixel clock divider less than 4\n");
		div = 0x40;
	}

	dev_dbg(mx3fb->dev, "pixel clk = %u, divider %u.%u\n",
		pixel_clk, div >> 4, (div & 7) * 125);

	spin_lock_irqsave(&mx3fb->lock, lock_flags);

	/*
	 * DISP3_IF_CLK_DOWN_WR is half the divider value and 2 fraction bits
	 * fewer. Subtract 1 extra from DISP3_IF_CLK_DOWN_WR based on timing
	 * debug. DISP3_IF_CLK_UP_WR is 0
	 */
	mx3fb_write_reg(mx3fb, (((div / 8) - 1) << 22) | div, DI_DISP3_TIME_CONF);

	/* DI settings */
	old_conf = mx3fb_read_reg(mx3fb, DI_DISP_IF_CONF) & 0x78FFFFFF;
	old_conf |= sig.datamask_en << DI_D3_DATAMSK_SHIFT |
		sig.clksel_en << DI_D3_CLK_SEL_SHIFT |
		sig.clkidle_en << DI_D3_CLK_IDLE_SHIFT;
	mx3fb_write_reg(mx3fb, old_conf, DI_DISP_IF_CONF);

	old_conf = mx3fb_read_reg(mx3fb, DI_DISP_SIG_POL) & 0xE0FFFFFF;
	old_conf |= sig.data_pol << DI_D3_DATA_POL_SHIFT |
		sig.clk_pol << DI_D3_CLK_POL_SHIFT |
		sig.enable_pol << DI_D3_DRDY_SHARP_POL_SHIFT |
		sig.Hsync_pol << DI_D3_HSYNC_POL_SHIFT |
		sig.Vsync_pol << DI_D3_VSYNC_POL_SHIFT;
	mx3fb_write_reg(mx3fb, old_conf, DI_DISP_SIG_POL);

	map = &di_mappings[mx3fb->disp_data_fmt];
	mx3fb_write_reg(mx3fb, map->b0, DI_DISP3_B0_MAP);
	mx3fb_write_reg(mx3fb, map->b1, DI_DISP3_B1_MAP);
	mx3fb_write_reg(mx3fb, map->b2, DI_DISP3_B2_MAP);

	spin_unlock_irqrestore(&mx3fb->lock, lock_flags);

	dev_dbg(mx3fb->dev, "DI_DISP_IF_CONF = 0x%08X\n",
		mx3fb_read_reg(mx3fb, DI_DISP_IF_CONF));
	dev_dbg(mx3fb->dev, "DI_DISP_SIG_POL = 0x%08X\n",
		mx3fb_read_reg(mx3fb, DI_DISP_SIG_POL));
	dev_dbg(mx3fb->dev, "DI_DISP3_TIME_CONF = 0x%08X\n",
		mx3fb_read_reg(mx3fb, DI_DISP3_TIME_CONF));

	return 0;
}