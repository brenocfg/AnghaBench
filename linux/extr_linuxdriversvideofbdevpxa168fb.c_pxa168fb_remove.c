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
struct pxa168fb_info {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; scalar_t__ reg_base; struct fb_info* info; } ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  smem_start; int /*<<< orphan*/  smem_len; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; TYPE_2__ cmap; } ;

/* Variables and functions */
 unsigned int CFG_GRA_ENA_MASK ; 
 unsigned int GRA_FRAME_IRQ0_ENA (int) ; 
 scalar_t__ LCD_SPU_DMA_CTRL0 ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ SPU_IRQ_ENA ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 struct pxa168fb_info* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pxa168fb_remove(struct platform_device *pdev)
{
	struct pxa168fb_info *fbi = platform_get_drvdata(pdev);
	struct fb_info *info;
	int irq;
	unsigned int data;

	if (!fbi)
		return 0;

	/* disable DMA transfer */
	data = readl(fbi->reg_base + LCD_SPU_DMA_CTRL0);
	data &= ~CFG_GRA_ENA_MASK;
	writel(data, fbi->reg_base + LCD_SPU_DMA_CTRL0);

	info = fbi->info;

	unregister_framebuffer(info);

	writel(GRA_FRAME_IRQ0_ENA(0x0), fbi->reg_base + SPU_IRQ_ENA);

	if (info->cmap.len)
		fb_dealloc_cmap(&info->cmap);

	irq = platform_get_irq(pdev, 0);

	dma_free_wc(fbi->dev, PAGE_ALIGN(info->fix.smem_len),
		    info->screen_base, info->fix.smem_start);

	clk_disable_unprepare(fbi->clk);

	framebuffer_release(info);

	return 0;
}