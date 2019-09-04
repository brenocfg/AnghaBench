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
 int /*<<< orphan*/  HEIGHT ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	switch (par->info->var.rotate) {
	/* R20h = Horizontal GRAM Start Address */
	/* R21h = Vertical GRAM Start Address */
	case 0:
		write_reg(par, 0x0020, xs);
		write_reg(par, 0x0021, ys);
		break;
	case 180:
		write_reg(par, 0x0020, WIDTH - 1 - xs);
		write_reg(par, 0x0021, HEIGHT - 1 - ys);
		break;
	case 270:
		write_reg(par, 0x0020, WIDTH - 1 - ys);
		write_reg(par, 0x0021, xs);
		break;
	case 90:
		write_reg(par, 0x0020, ys);
		write_reg(par, 0x0021, HEIGHT - 1 - xs);
		break;
	}
	write_reg(par, 0x0022); /* Write Data to GRAM */
}