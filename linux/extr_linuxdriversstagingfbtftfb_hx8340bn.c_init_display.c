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
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_PIXEL_FMT_16BIT ; 
 int MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	/* BTL221722-276L startup sequence, from datasheet */

	/*
	 * SETEXTCOM: Set extended command set (C1h)
	 * This command is used to set extended command set access enable.
	 * Enable: After command (C1h), must write: ffh,83h,40h
	 */
	write_reg(par, 0xC1, 0xFF, 0x83, 0x40);

	/*
	 * Sleep out
	 * This command turns off sleep mode.
	 * In this mode the DC/DC converter is enabled, Internal oscillator
	 * is started, and panel scanning is started.
	 */
	write_reg(par, 0x11);
	mdelay(150);

	/* Undoc'd register? */
	write_reg(par, 0xCA, 0x70, 0x00, 0xD9);

	/*
	 * SETOSC: Set Internal Oscillator (B0h)
	 * This command is used to set internal oscillator related settings
	 *	OSC_EN: Enable internal oscillator
	 *	Internal oscillator frequency: 125% x 2.52MHz
	 */
	write_reg(par, 0xB0, 0x01, 0x11);

	/* Drive ability setting */
	write_reg(par, 0xC9, 0x90, 0x49, 0x10, 0x28, 0x28, 0x10, 0x00, 0x06);
	mdelay(20);

	/*
	 * SETPWCTR5: Set Power Control 5(B5h)
	 * This command is used to set VCOM Low and VCOM High Voltage
	 * VCOMH 0110101 :  3.925
	 * VCOML 0100000 : -1.700
	 * 45h=69  VCOMH: "VMH" + 5d   VCOML: "VMH" + 5d
	 */
	write_reg(par, 0xB5, 0x35, 0x20, 0x45);

	/*
	 * SETPWCTR4: Set Power Control 4(B4h)
	 *	VRH[4:0]:	Specify the VREG1 voltage adjusting.
	 *			VREG1 voltage is for gamma voltage setting.
	 *	BT[2:0]:	Switch the output factor of step-up circuit 2
	 *			for VGH and VGL voltage generation.
	 */
	write_reg(par, 0xB4, 0x33, 0x25, 0x4C);
	mdelay(10);

	/*
	 * Interface Pixel Format (3Ah)
	 * This command is used to define the format of RGB picture data,
	 * which is to be transfer via the system and RGB interface.
	 * RGB interface: 16 Bit/Pixel
	 */
	write_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);

	/*
	 * Display on (29h)
	 * This command is used to recover from DISPLAY OFF mode.
	 * Output from the Frame Memory is enabled.
	 */
	write_reg(par, MIPI_DCS_SET_DISPLAY_ON);
	mdelay(10);

	return 0;
}