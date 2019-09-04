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
typedef  int u8 ;
struct fbtft_par {scalar_t__ bgr; TYPE_2__* info; } ;
struct TYPE_3__ {int rotate; } ;
struct TYPE_4__ {TYPE_1__ var; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int set_var(struct fbtft_par *par)
{
	u8 mactrl_data = 0; /* Avoid compiler warning */

	switch (par->info->var.rotate) {
	case 0:
		mactrl_data = 0x08;
		break;
	case 180:
		mactrl_data = 0xC8;
		break;
	case 270:
		mactrl_data = 0xA8;
		break;
	case 90:
		mactrl_data = 0x68;
		break;
	}

	/* Colorspcae */
	if (par->bgr)
		mactrl_data |= BIT(2);
	write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, mactrl_data);
	write_reg(par, MIPI_DCS_WRITE_MEMORY_START);
	return 0;
}