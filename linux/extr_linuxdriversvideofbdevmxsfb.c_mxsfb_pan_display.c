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
struct mxsfb_info {TYPE_1__* devdata; scalar_t__ base; } ;
struct fb_var_screeninfo {scalar_t__ xoffset; unsigned int yoffset; } ;
struct TYPE_4__ {unsigned int line_length; scalar_t__ smem_start; } ;
struct fb_info {TYPE_2__ fix; struct mxsfb_info* par; } ;
struct TYPE_3__ {scalar_t__ next_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mxsfb_pan_display(struct fb_var_screeninfo *var,
		struct fb_info *fb_info)
{
	struct mxsfb_info *host = fb_info->par;
	unsigned offset;

	if (var->xoffset != 0)
		return -EINVAL;

	offset = fb_info->fix.line_length * var->yoffset;

	mxsfb_enable_axi_clk(host);

	/* update on next VSYNC */
	writel(fb_info->fix.smem_start + offset,
			host->base + host->devdata->next_buf);

	mxsfb_disable_axi_clk(host);

	return 0;
}