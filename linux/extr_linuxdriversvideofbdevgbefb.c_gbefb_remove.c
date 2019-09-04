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
typedef  int /*<<< orphan*/  uint16_t ;
struct sgi_gbe {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gbefb_par {int /*<<< orphan*/  wc_cookie; } ;
struct fb_info {struct gbefb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; scalar_t__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_BASE ; 
 int GBE_TLB_SIZE ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 scalar_t__ gbe_dma_addr ; 
 int /*<<< orphan*/  gbe_mem ; 
 int /*<<< orphan*/  gbe_mem_phys ; 
 int /*<<< orphan*/  gbe_mem_size ; 
 TYPE_1__ gbe_tiles ; 
 int /*<<< orphan*/  gbe_turn_off () ; 
 int /*<<< orphan*/  gbefb_remove_sysfs (int /*<<< orphan*/ *) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int gbefb_remove(struct platform_device* p_dev)
{
	struct fb_info *info = platform_get_drvdata(p_dev);
	struct gbefb_par *par = info->par;

	unregister_framebuffer(info);
	gbe_turn_off();
	arch_phys_wc_del(par->wc_cookie);
	if (gbe_dma_addr)
		dma_free_wc(NULL, gbe_mem_size, gbe_mem, gbe_mem_phys);
	dma_free_coherent(NULL, GBE_TLB_SIZE * sizeof(uint16_t),
			  (void *)gbe_tiles.cpu, gbe_tiles.dma);
	release_mem_region(GBE_BASE, sizeof(struct sgi_gbe));
	gbefb_remove_sysfs(&p_dev->dev);
	framebuffer_release(info);

	return 0;
}