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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int scan_align; int buf_align; int /*<<< orphan*/  flags; scalar_t__ size; int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {unsigned long smem_len; } ;
struct fb_info {TYPE_2__* fbops; TYPE_1__ sprite; TYPE_3__ fix; scalar_t__ screen_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  fb_cursor; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FB_PIXMAP_IO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  atyfb_cursor ; 

int aty_init_cursor(struct fb_info *info)
{
	unsigned long addr;

	info->fix.smem_len -= PAGE_SIZE;

#ifdef __sparc__
	addr = (unsigned long) info->screen_base - 0x800000 + info->fix.smem_len;
	info->sprite.addr = (u8 *) addr;
#else
#ifdef __BIG_ENDIAN
	addr = info->fix.smem_start - 0x800000 + info->fix.smem_len;
	info->sprite.addr = (u8 *) ioremap(addr, 1024);
#else
	addr = (unsigned long) info->screen_base + info->fix.smem_len;
	info->sprite.addr = (u8 *) addr;
#endif
#endif
	if (!info->sprite.addr)
		return -ENXIO;
	info->sprite.size = PAGE_SIZE;
	info->sprite.scan_align = 16;	/* Scratch pad 64 bytes wide */
	info->sprite.buf_align = 16; 	/* and 64 lines tall. */
	info->sprite.flags = FB_PIXMAP_IO;

	info->fbops->fb_cursor = atyfb_cursor;

	return 0;
}