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
struct TYPE_6__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;int /*<<< orphan*/  register_backlight; } ;
struct fbtft_par {TYPE_3__ fbtftops; TYPE_2__* pdata; } ;
struct TYPE_4__ {scalar_t__ backlight; } ;
struct TYPE_5__ {TYPE_1__ display; } ;

/* Variables and functions */
 scalar_t__ FBTFT_ONBOARD_BACKLIGHT ; 
 int /*<<< orphan*/  register_onboard_backlight ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	if (par->pdata &&
	    par->pdata->display.backlight == FBTFT_ONBOARD_BACKLIGHT) {
		/* module uses onboard GPIO for panel power */
		par->fbtftops.register_backlight = register_onboard_backlight;
	}

	par->fbtftops.reset(par);

	write_reg(par, 0xfd, 0x12); /* Command Lock */
	write_reg(par, 0xfd, 0xb1); /* Command Lock */
	write_reg(par, 0xae); /* Display Off */
	write_reg(par, 0xb3, 0xf1); /* Front Clock Div */
	write_reg(par, 0xca, 0x7f); /* Set Mux Ratio */
	write_reg(par, 0x15, 0x00, 0x7f); /* Set Column Address */
	write_reg(par, 0x75, 0x00, 0x7f); /* Set Row Address */
	write_reg(par, 0xa1, 0x00); /* Set Display Start Line */
	write_reg(par, 0xa2, 0x00); /* Set Display Offset */
	write_reg(par, 0xb5, 0x00); /* Set GPIO */
	write_reg(par, 0xab, 0x01); /* Set Function Selection */
	write_reg(par, 0xb1, 0x32); /* Set Phase Length */
	write_reg(par, 0xb4, 0xa0, 0xb5, 0x55); /* Set Segment Low Voltage */
	write_reg(par, 0xbb, 0x17); /* Set Precharge Voltage */
	write_reg(par, 0xbe, 0x05); /* Set VComH Voltage */
	write_reg(par, 0xc1, 0xc8, 0x80, 0xc8); /* Set Contrast */
	write_reg(par, 0xc7, 0x0f); /* Set Master Contrast */
	write_reg(par, 0xb6, 0x01); /* Set Second Precharge Period */
	write_reg(par, 0xa6); /* Set Display Mode Reset */
	write_reg(par, 0xaf); /* Set Sleep Mode Display On */

	return 0;
}