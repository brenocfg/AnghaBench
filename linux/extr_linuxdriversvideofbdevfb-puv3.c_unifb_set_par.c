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
struct TYPE_4__ {int xres_virtual; int bits_per_pixel; int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; } ;
struct TYPE_3__ {int line_length; int smem_start; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UDE_CFG ; 
 int UDE_CFG_DST16 ; 
 int UDE_CFG_DST24 ; 
 int UDE_CFG_DST32 ; 
 int UDE_CFG_DST8 ; 
 int UDE_CFG_GDEN_ENABLE ; 
 int UDE_CFG_TIMEUP_ENABLE ; 
 int /*<<< orphan*/  UDE_FSA ; 
 int /*<<< orphan*/  UDE_HAT ; 
 int /*<<< orphan*/  UDE_HBT ; 
 int /*<<< orphan*/  UDE_HST ; 
 int /*<<< orphan*/  UDE_LS ; 
 int /*<<< orphan*/  UDE_PS ; 
 int /*<<< orphan*/  UDE_VAT ; 
 int /*<<< orphan*/  UDE_VBT ; 
 int /*<<< orphan*/  UDE_VST ; 
 int get_line_length (int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unifb_set_par(struct fb_info *info)
{
	int hTotal, vTotal, hSyncStart, hSyncEnd, vSyncStart, vSyncEnd;
	int format;

#ifdef CONFIG_PUV3_PM
	struct clk *clk_vga;
	u32 pixclk = 0;
	int i;

	for (i = 0; i <= 10; i++) {
		if    (info->var.xres         == unifb_modes[i].xres
		    && info->var.yres         == unifb_modes[i].yres
		    && info->var.upper_margin == unifb_modes[i].upper_margin
		    && info->var.lower_margin == unifb_modes[i].lower_margin
		    && info->var.left_margin  == unifb_modes[i].left_margin
		    && info->var.right_margin == unifb_modes[i].right_margin
		    && info->var.hsync_len    == unifb_modes[i].hsync_len
		    && info->var.vsync_len    == unifb_modes[i].vsync_len) {
			pixclk = unifb_modes[i].pixclock;
			break;
		}
	}

	/* set clock rate */
	clk_vga = clk_get(info->device, "VGA_CLK");
	if (clk_vga == ERR_PTR(-ENOENT))
		return -ENOENT;

	if (pixclk != 0) {
		if (clk_set_rate(clk_vga, pixclk)) { /* set clock failed */
			info->fix = unifb_fix;
			info->var = unifb_default;
			if (clk_set_rate(clk_vga, unifb_default.pixclock))
				return -EINVAL;
		}
	}
#endif

	info->fix.line_length = get_line_length(info->var.xres_virtual,
						info->var.bits_per_pixel);

	hSyncStart = info->var.xres + info->var.right_margin;
	hSyncEnd = hSyncStart + info->var.hsync_len;
	hTotal = hSyncEnd + info->var.left_margin;

	vSyncStart = info->var.yres + info->var.lower_margin;
	vSyncEnd = vSyncStart + info->var.vsync_len;
	vTotal = vSyncEnd + info->var.upper_margin;

	switch (info->var.bits_per_pixel) {
	case 8:
		format = UDE_CFG_DST8;
		break;
	case 16:
		format = UDE_CFG_DST16;
		break;
	case 24:
		format = UDE_CFG_DST24;
		break;
	case 32:
		format = UDE_CFG_DST32;
		break;
	default:
		return -EINVAL;
	}

	writel(info->fix.smem_start, UDE_FSA);
	writel(info->var.yres, UDE_LS);
	writel(get_line_length(info->var.xres,
			info->var.bits_per_pixel) >> 3, UDE_PS);
			/* >> 3 for hardware required. */
	writel((hTotal << 16) | (info->var.xres), UDE_HAT);
	writel(((hTotal - 1) << 16) | (info->var.xres - 1), UDE_HBT);
	writel(((hSyncEnd - 1) << 16) | (hSyncStart - 1), UDE_HST);
	writel((vTotal << 16) | (info->var.yres), UDE_VAT);
	writel(((vTotal - 1) << 16) | (info->var.yres - 1), UDE_VBT);
	writel(((vSyncEnd - 1) << 16) | (vSyncStart - 1), UDE_VST);
	writel(UDE_CFG_GDEN_ENABLE | UDE_CFG_TIMEUP_ENABLE
			| format | 0xC0000001, UDE_CFG);

	return 0;
}