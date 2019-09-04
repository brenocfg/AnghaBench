#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vbox_private {scalar_t__ available_vram_size; TYPE_2__* fbdev; } ;
struct TYPE_10__ {scalar_t__ smem_len; scalar_t__ smem_start; } ;
struct fb_info {TYPE_5__ fix; TYPE_4__* apertures; } ;
struct TYPE_9__ {TYPE_3__* ranges; } ;
struct TYPE_8__ {scalar_t__ base; } ;
struct TYPE_6__ {struct fb_info* fbdev; } ;
struct TYPE_7__ {TYPE_1__ helper; } ;

/* Variables and functions */

void vbox_fbdev_set_base(struct vbox_private *vbox, unsigned long gpu_addr)
{
	struct fb_info *fbdev = vbox->fbdev->helper.fbdev;

	fbdev->fix.smem_start = fbdev->apertures->ranges[0].base + gpu_addr;
	fbdev->fix.smem_len = vbox->available_vram_size - gpu_addr;
}