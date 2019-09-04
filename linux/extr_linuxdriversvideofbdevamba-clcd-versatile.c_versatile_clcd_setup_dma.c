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
struct TYPE_6__ {unsigned long smem_len; int /*<<< orphan*/  smem_start; } ;
struct TYPE_5__ {TYPE_3__ fix; int /*<<< orphan*/  screen_base; } ;
struct clcd_fb {TYPE_2__ fb; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int versatile_clcd_setup_dma(struct clcd_fb *fb, unsigned long framesize)
{
	dma_addr_t dma;

	fb->fb.screen_base = dma_alloc_wc(&fb->dev->dev, framesize, &dma,
					  GFP_KERNEL);
	if (!fb->fb.screen_base) {
		pr_err("CLCD: unable to map framebuffer\n");
		return -ENOMEM;
	}

	fb->fb.fix.smem_start	= dma;
	fb->fb.fix.smem_len	= framesize;

	return 0;
}