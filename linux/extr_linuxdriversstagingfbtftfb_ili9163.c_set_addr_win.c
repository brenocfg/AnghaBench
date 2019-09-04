#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fbtft_par {TYPE_2__* info; } ;
struct TYPE_3__ {int rotate; } ;
struct TYPE_4__ {TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_COLUMN_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PAGE_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int /*<<< orphan*/  __OFFSET ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys,
			 int xe, int ye)
{
	switch (par->info->var.rotate) {
	case 0:
		write_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		write_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  (ys + __OFFSET) >> 8, (ys + __OFFSET) & 0xff,
			  (ye + __OFFSET) >> 8, (ye + __OFFSET) & 0xff);
		break;
	case 90:
		write_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  (xs + __OFFSET) >> 8, (xs + __OFFSET) & 0xff,
			  (xe + __OFFSET) >> 8, (xe + __OFFSET) & 0xff);
		write_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		break;
	case 180:
	case 270:
		write_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		write_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		break;
	default:
		/* Fix incorrect setting */
		par->info->var.rotate = 0;
	}
	write_reg(par, MIPI_DCS_WRITE_MEMORY_START);
}