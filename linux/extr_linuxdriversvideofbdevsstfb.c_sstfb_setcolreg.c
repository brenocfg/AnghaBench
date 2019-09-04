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
typedef  int u_int ;
typedef  int u32 ;
struct sstfb_par {int* palette; } ;
struct TYPE_9__ {int length; int offset; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int length; int offset; } ;
struct TYPE_6__ {int length; int offset; } ;
struct TYPE_10__ {TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {TYPE_5__ var; struct sstfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  f_dddprintk (char*,...) ; 

__attribute__((used)) static int sstfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
                           u_int transp, struct fb_info *info)
{
	struct sstfb_par *par = info->par;
	u32 col;

	f_dddprintk("sstfb_setcolreg\n");
	f_dddprintk("%-2d rgbt: %#x, %#x, %#x, %#x\n",
	            regno, red, green, blue, transp);
	if (regno > 15)
		return 0;

	red    >>= (16 - info->var.red.length);
	green  >>= (16 - info->var.green.length);
	blue   >>= (16 - info->var.blue.length);
	transp >>= (16 - info->var.transp.length);
	col = (red << info->var.red.offset)
	    | (green << info->var.green.offset)
	    | (blue  << info->var.blue.offset)
	    | (transp << info->var.transp.offset);
	
	par->palette[regno] = col;

	return 0;
}