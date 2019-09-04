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
struct nuc900fb_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_start; int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; struct nuc900fb_info* par; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct nuc900fb_info*,unsigned long) ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int nuc900fb_map_video_memory(struct fb_info *info)
{
	struct nuc900fb_info *fbi = info->par;
	dma_addr_t map_dma;
	unsigned long map_size = PAGE_ALIGN(info->fix.smem_len);

	dev_dbg(fbi->dev, "nuc900fb_map_video_memory(fbi=%p) map_size %lu\n",
		fbi, map_size);

	info->screen_base = dma_alloc_wc(fbi->dev, map_size, &map_dma,
					 GFP_KERNEL);

	if (!info->screen_base)
		return -ENOMEM;

	memset(info->screen_base, 0x00, map_size);
	info->fix.smem_start = map_dma;

	return 0;
}