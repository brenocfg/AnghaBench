#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct jzfb {int vidmem_size; void* vidmem; int /*<<< orphan*/  framedesc_phys; TYPE_3__* framedesc; TYPE_2__* pdev; int /*<<< orphan*/  vidmem_phys; TYPE_1__* pdata; } ;
struct fb_videomode {int xres; int yres; } ;
struct TYPE_6__ {int id; int cmd; int /*<<< orphan*/  addr; int /*<<< orphan*/  next; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int num_modes; struct fb_videomode* modes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int jzfb_get_controller_bpp (struct jzfb*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int jzfb_alloc_devmem(struct jzfb *jzfb)
{
	int max_videosize = 0;
	struct fb_videomode *mode = jzfb->pdata->modes;
	void *page;
	int i;

	for (i = 0; i < jzfb->pdata->num_modes; ++mode, ++i) {
		if (max_videosize < mode->xres * mode->yres)
			max_videosize = mode->xres * mode->yres;
	}

	max_videosize *= jzfb_get_controller_bpp(jzfb) >> 3;

	jzfb->framedesc = dma_alloc_coherent(&jzfb->pdev->dev,
					sizeof(*jzfb->framedesc),
					&jzfb->framedesc_phys, GFP_KERNEL);

	if (!jzfb->framedesc)
		return -ENOMEM;

	jzfb->vidmem_size = PAGE_ALIGN(max_videosize);
	jzfb->vidmem = dma_alloc_coherent(&jzfb->pdev->dev,
					jzfb->vidmem_size,
					&jzfb->vidmem_phys, GFP_KERNEL);

	if (!jzfb->vidmem)
		goto err_free_framedesc;

	for (page = jzfb->vidmem;
		 page < jzfb->vidmem + PAGE_ALIGN(jzfb->vidmem_size);
		 page += PAGE_SIZE) {
		SetPageReserved(virt_to_page(page));
	}

	jzfb->framedesc->next = jzfb->framedesc_phys;
	jzfb->framedesc->addr = jzfb->vidmem_phys;
	jzfb->framedesc->id = 0xdeafbead;
	jzfb->framedesc->cmd = 0;
	jzfb->framedesc->cmd |= max_videosize / 4;

	return 0;

err_free_framedesc:
	dma_free_coherent(&jzfb->pdev->dev, sizeof(*jzfb->framedesc),
				jzfb->framedesc, jzfb->framedesc_phys);
	return -ENOMEM;
}