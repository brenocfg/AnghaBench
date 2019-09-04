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
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	switch (par->info->var.rotate) {
	case 90:
	case 270:
		/* Set column address */
		write_reg(par, ys & 0x0F);
		write_reg(par, 0x10 | (ys >> 4));

		/* Set page address (divide xs by 2) (not used by driver) */
		write_reg(par, 0x60 | ((xs >> 1) & 0x0F));
		write_reg(par, 0x70 | (xs >> 5));
		break;
	default:
		/* Set column address (not used by driver) */
		write_reg(par, xs & 0x0F);
		write_reg(par, 0x10 | (xs >> 4));

		/* Set page address (divide ys by 2) */
		write_reg(par, 0x60 | ((ys >> 1) & 0x0F));
		write_reg(par, 0x70 | (ys >> 5));
		break;
	}
}