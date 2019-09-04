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
struct fb_var_screeninfo {scalar_t__ xoffset; scalar_t__ yoffset; int bits_per_pixel; unsigned int yres; } ;
struct fb_fix_screeninfo {int smem_start; int line_length; } ;
struct fb_info {struct fb_var_screeninfo var; struct fb_fix_screeninfo fix; struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {unsigned int dma_start; unsigned int dma_end; int which_dma_channel_done; int /*<<< orphan*/  lock_for_chan_update; } ;
typedef  int /*<<< orphan*/  new_var ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_BASE_ADDR_0_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_BASE_ADDR_1_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG ; 
 scalar_t__ fb_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  lcdc_write (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int da8xx_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *fbi)
{
	int ret = 0;
	struct fb_var_screeninfo new_var;
	struct da8xx_fb_par         *par = fbi->par;
	struct fb_fix_screeninfo    *fix = &fbi->fix;
	unsigned int end;
	unsigned int start;
	unsigned long irq_flags;

	if (var->xoffset != fbi->var.xoffset ||
			var->yoffset != fbi->var.yoffset) {
		memcpy(&new_var, &fbi->var, sizeof(new_var));
		new_var.xoffset = var->xoffset;
		new_var.yoffset = var->yoffset;
		if (fb_check_var(&new_var, fbi))
			ret = -EINVAL;
		else {
			memcpy(&fbi->var, &new_var, sizeof(new_var));

			start	= fix->smem_start +
				new_var.yoffset * fix->line_length +
				new_var.xoffset * fbi->var.bits_per_pixel / 8;
			end	= start + fbi->var.yres * fix->line_length - 1;
			par->dma_start	= start;
			par->dma_end	= end;
			spin_lock_irqsave(&par->lock_for_chan_update,
					irq_flags);
			if (par->which_dma_channel_done == 0) {
				lcdc_write(par->dma_start,
					   LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
				lcdc_write(par->dma_end,
					   LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
			} else if (par->which_dma_channel_done == 1) {
				lcdc_write(par->dma_start,
					   LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
				lcdc_write(par->dma_end,
					   LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
			}
			spin_unlock_irqrestore(&par->lock_for_chan_update,
					irq_flags);
		}
	}

	return ret;
}