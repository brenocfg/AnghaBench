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
struct mx3fb_platform_data {char* name; int disp_data_fmt; int num_modes; struct fb_videomode* mode; } ;
struct mx3fb_info {scalar_t__ ipu_ch; int /*<<< orphan*/  flip_cmpl; int /*<<< orphan*/  blank; struct mx3fb_data* mx3fb; struct idmac_channel* idmac_channel; } ;
struct mx3fb_data {int disp_data_fmt; struct device* dev; struct fb_info* fbi; } ;
struct TYPE_3__ {scalar_t__ chan_id; } ;
struct idmac_channel {unsigned int eof_irq; TYPE_1__ dma_chan; struct mx3fb_data* client; } ;
struct fb_videomode {int dummy; } ;
struct TYPE_4__ {int yres_virtual; int yres; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct mx3fb_info* par; TYPE_2__ var; int /*<<< orphan*/  modelist; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fb_videomode*) ; 
 int /*<<< orphan*/  DI_HSP_CLK_PER ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_NORMAL ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IDMAC_SDC_0 ; 
 int /*<<< orphan*/  __blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int __set_par (struct fb_info*,int) ; 
 int /*<<< orphan*/  default_bpp ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct mx3fb_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*) ; 
 struct fb_videomode* di_mappings ; 
 int /*<<< orphan*/  disable_irq (unsigned int) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_find_mode (TYPE_2__*,struct fb_info*,char const*,struct fb_videomode const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* fb_mode ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (struct fb_videomode const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct fb_info* mx3fb_init_fbinfo (struct device*,int /*<<< orphan*/ *) ; 
 struct fb_videomode* mx3fb_modedb ; 
 int /*<<< orphan*/  mx3fb_ops ; 
 int /*<<< orphan*/  mx3fb_write_reg (struct mx3fb_data*,int,int /*<<< orphan*/ ) ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  sdc_set_brightness (struct mx3fb_data*,int) ; 
 int /*<<< orphan*/  sdc_set_color_key (struct mx3fb_data*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdc_set_global_alpha (struct mx3fb_data*,int,int) ; 

__attribute__((used)) static int init_fb_chan(struct mx3fb_data *mx3fb, struct idmac_channel *ichan)
{
	struct device *dev = mx3fb->dev;
	struct mx3fb_platform_data *mx3fb_pdata = dev_get_platdata(dev);
	const char *name = mx3fb_pdata->name;
	unsigned int irq;
	struct fb_info *fbi;
	struct mx3fb_info *mx3fbi;
	const struct fb_videomode *mode;
	int ret, num_modes;

	if (mx3fb_pdata->disp_data_fmt >= ARRAY_SIZE(di_mappings)) {
		dev_err(dev, "Illegal display data format %d\n",
				mx3fb_pdata->disp_data_fmt);
		return -EINVAL;
	}

	ichan->client = mx3fb;
	irq = ichan->eof_irq;

	if (ichan->dma_chan.chan_id != IDMAC_SDC_0)
		return -EINVAL;

	fbi = mx3fb_init_fbinfo(dev, &mx3fb_ops);
	if (!fbi)
		return -ENOMEM;

	if (!fb_mode)
		fb_mode = name;

	if (!fb_mode) {
		ret = -EINVAL;
		goto emode;
	}

	if (mx3fb_pdata->mode && mx3fb_pdata->num_modes) {
		mode = mx3fb_pdata->mode;
		num_modes = mx3fb_pdata->num_modes;
	} else {
		mode = mx3fb_modedb;
		num_modes = ARRAY_SIZE(mx3fb_modedb);
	}

	if (!fb_find_mode(&fbi->var, fbi, fb_mode, mode,
			  num_modes, NULL, default_bpp)) {
		ret = -EBUSY;
		goto emode;
	}

	fb_videomode_to_modelist(mode, num_modes, &fbi->modelist);

	/* Default Y virtual size is 2x panel size */
	fbi->var.yres_virtual = fbi->var.yres * 2;

	mx3fb->fbi = fbi;

	/* set Display Interface clock period */
	mx3fb_write_reg(mx3fb, 0x00100010L, DI_HSP_CLK_PER);
	/* Might need to trigger HSP clock change - see 44.3.3.8.5 */

	sdc_set_brightness(mx3fb, 255);
	sdc_set_global_alpha(mx3fb, true, 0xFF);
	sdc_set_color_key(mx3fb, IDMAC_SDC_0, false, 0);

	mx3fbi			= fbi->par;
	mx3fbi->idmac_channel	= ichan;
	mx3fbi->ipu_ch		= ichan->dma_chan.chan_id;
	mx3fbi->mx3fb		= mx3fb;
	mx3fbi->blank		= FB_BLANK_NORMAL;

	mx3fb->disp_data_fmt	= mx3fb_pdata->disp_data_fmt;

	init_completion(&mx3fbi->flip_cmpl);
	disable_irq(ichan->eof_irq);
	dev_dbg(mx3fb->dev, "disabling irq %d\n", ichan->eof_irq);
	ret = __set_par(fbi, false);
	if (ret < 0)
		goto esetpar;

	__blank(FB_BLANK_UNBLANK, fbi);

	dev_info(dev, "registered, using mode %s\n", fb_mode);

	ret = register_framebuffer(fbi);
	if (ret < 0)
		goto erfb;

	return 0;

erfb:
esetpar:
emode:
	fb_dealloc_cmap(&fbi->cmap);
	framebuffer_release(fbi);

	return ret;
}