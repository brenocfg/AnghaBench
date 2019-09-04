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
typedef  int u_int ;
struct fb_var_screeninfo {int yoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */

__attribute__((used)) static inline void
acornfb_update_dma(struct fb_info *info, struct fb_var_screeninfo *var)
{
	u_int off = var->yoffset * info->fix.line_length;

#if defined(HAS_MEMC)
	memc_write(VDMA_INIT, off >> 2);
#elif defined(HAS_IOMD)
	iomd_writel(info->fix.smem_start + off, IOMD_VIDINIT);
#endif
}