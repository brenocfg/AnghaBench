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
struct fb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clut_data; int /*<<< orphan*/  clut_waddr; } ;

/* Variables and functions */
 TYPE_1__* csc_cmap_regs ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nubus_writeb (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int csc_setpalette(unsigned int regno, unsigned int red,
			  unsigned int green, unsigned int blue,
			  struct fb_info *info)
{
	unsigned long flags;

	local_irq_save(flags);

	udelay(1); /* mklinux on PB 5300 waits for 260 ns */
	nubus_writeb(regno, &csc_cmap_regs->clut_waddr);
	nubus_writeb(red, &csc_cmap_regs->clut_data);
	nubus_writeb(green, &csc_cmap_regs->clut_data);
	nubus_writeb(blue, &csc_cmap_regs->clut_data);

	local_irq_restore(flags);
	return 0;
}