#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fbtft_par {TYPE_6__* info; } ;
struct TYPE_10__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_9__ {int length; scalar_t__ offset; } ;
struct TYPE_8__ {int length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_11__ {int grayscale; int rotate; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct TYPE_12__ {TYPE_5__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int set_var(struct fbtft_par *par)
{
	/* par->info->fix.visual = FB_VISUAL_PSEUDOCOLOR; */
	par->info->var.grayscale = 1;
	par->info->var.red.offset    = 0;
	par->info->var.red.length    = 8;
	par->info->var.green.offset  = 0;
	par->info->var.green.length  = 8;
	par->info->var.blue.offset   = 0;
	par->info->var.blue.length   = 8;
	par->info->var.transp.offset = 0;
	par->info->var.transp.length = 0;

	switch (par->info->var.rotate) {
	case 90:
		/* Set RAM address control */
		write_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x1 & 0x1) << 1 /* Increment page first */
			| (0x1 & 0x1));    /* Wrap around (default) */

		/* Set LCD mapping */
		write_reg(par, 0xC0
			| (0x0 & 0x1) << 2 /* Mirror Y OFF */
			| (0x0 & 0x1) << 1 /* Mirror X OFF */
			| (0x0 & 0x1));    /* MS nibble last (default) */
		break;
	case 180:
		/* Set RAM address control */
		write_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x0 & 0x1) << 1 /* Increment column first */
			| (0x1 & 0x1));    /* Wrap around (default) */

		/* Set LCD mapping */
		write_reg(par, 0xC0
			| (0x1 & 0x1) << 2 /* Mirror Y ON */
			| (0x0 & 0x1) << 1 /* Mirror X OFF */
			| (0x0 & 0x1));    /* MS nibble last (default) */
		break;
	case 270:
		/* Set RAM address control */
		write_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x1 & 0x1) << 1 /* Increment page first */
			| (0x1 & 0x1));    /* Wrap around (default) */

		/* Set LCD mapping */
		write_reg(par, 0xC0
			| (0x1 & 0x1) << 2 /* Mirror Y ON */
			| (0x1 & 0x1) << 1 /* Mirror X ON */
			| (0x0 & 0x1));    /* MS nibble last (default) */
		break;
	default:
		/* Set RAM address control */
		write_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x0 & 0x1) << 1 /* Increment column first */
			| (0x1 & 0x1));    /* Wrap around (default) */

		/* Set LCD mapping */
		write_reg(par, 0xC0
			| (0x0 & 0x1) << 2 /* Mirror Y OFF */
			| (0x1 & 0x1) << 1 /* Mirror X ON */
			| (0x0 & 0x1));    /* MS nibble last (default) */
		break;
	}

	return 0;
}