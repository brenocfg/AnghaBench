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
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int,...) ; 

__attribute__((used)) static int set_var(struct fbtft_par *par)
{
	switch (par->info->var.rotate) {
	case 270:
		write_reg(par, 0xB6, 0x00, 0x02, 0x3B);
		write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x28);
		break;
	case 180:
		write_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x58);
		break;
	case 90:
		write_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x38);
		break;
	default:
		write_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x08);
		break;
	}

	return 0;
}