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
typedef  int u32 ;
struct videomode {int flags; } ;
struct mxsfb_info {int /*<<< orphan*/  sync; int /*<<< orphan*/  ld_intf_width; TYPE_1__* pdev; } ;
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int bits_per_pixel; } ;
struct fb_info {struct fb_var_screeninfo var; struct mxsfb_info* par; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DE_HIGH ; 
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  MXSFB_SYNC_DATA_ENABLE_HIGH_ACT ; 
 int /*<<< orphan*/  MXSFB_SYNC_DOTCLK_FALLING_ACT ; 
 int /*<<< orphan*/  OF_USE_NATIVE_MODE ; 
 int /*<<< orphan*/  STMLCDIF_16BIT ; 
 int /*<<< orphan*/  STMLCDIF_18BIT ; 
 int /*<<< orphan*/  STMLCDIF_24BIT ; 
 int /*<<< orphan*/  STMLCDIF_8BIT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int fb_videomode_from_videomode (struct videomode*,struct fb_videomode*) ; 
 int of_get_videomode (struct device_node*,struct videomode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int mxsfb_init_fbinfo_dt(struct fb_info *fb_info,
				struct fb_videomode *vmode)
{
	struct mxsfb_info *host = fb_info->par;
	struct fb_var_screeninfo *var = &fb_info->var;
	struct device *dev = &host->pdev->dev;
	struct device_node *np = host->pdev->dev.of_node;
	struct device_node *display_np;
	struct videomode vm;
	u32 width;
	int ret;

	display_np = of_parse_phandle(np, "display", 0);
	if (!display_np) {
		dev_err(dev, "failed to find display phandle\n");
		return -ENOENT;
	}

	ret = of_property_read_u32(display_np, "bus-width", &width);
	if (ret < 0) {
		dev_err(dev, "failed to get property bus-width\n");
		goto put_display_node;
	}

	switch (width) {
	case 8:
		host->ld_intf_width = STMLCDIF_8BIT;
		break;
	case 16:
		host->ld_intf_width = STMLCDIF_16BIT;
		break;
	case 18:
		host->ld_intf_width = STMLCDIF_18BIT;
		break;
	case 24:
		host->ld_intf_width = STMLCDIF_24BIT;
		break;
	default:
		dev_err(dev, "invalid bus-width value\n");
		ret = -EINVAL;
		goto put_display_node;
	}

	ret = of_property_read_u32(display_np, "bits-per-pixel",
				   &var->bits_per_pixel);
	if (ret < 0) {
		dev_err(dev, "failed to get property bits-per-pixel\n");
		goto put_display_node;
	}

	ret = of_get_videomode(display_np, &vm, OF_USE_NATIVE_MODE);
	if (ret) {
		dev_err(dev, "failed to get videomode from DT\n");
		goto put_display_node;
	}

	ret = fb_videomode_from_videomode(&vm, vmode);
	if (ret < 0)
		goto put_display_node;

	if (vm.flags & DISPLAY_FLAGS_DE_HIGH)
		host->sync |= MXSFB_SYNC_DATA_ENABLE_HIGH_ACT;

	/*
	 * The PIXDATA flags of the display_flags enum are controller
	 * centric, e.g. NEGEDGE means drive data on negative edge.
	 * However, the drivers flag is display centric: Sample the
	 * data on negative (falling) edge. Therefore, check for the
	 * POSEDGE flag:
	 * drive on positive edge => sample on negative edge
	 */
	if (vm.flags & DISPLAY_FLAGS_PIXDATA_POSEDGE)
		host->sync |= MXSFB_SYNC_DOTCLK_FALLING_ACT;

put_display_node:
	of_node_put(display_np);
	return ret;
}