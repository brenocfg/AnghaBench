#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int FMsk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSCOEFF0 ; 
 int /*<<< orphan*/  HSCOEFF1 ; 
 int /*<<< orphan*/  HSCOEFF2 ; 
 int /*<<< orphan*/  HSCOEFF3 ; 
 int /*<<< orphan*/  HSCOEFF4 ; 
 int /*<<< orphan*/  HSCOEFF5 ; 
 int /*<<< orphan*/  HSCOEFF6 ; 
 int /*<<< orphan*/  HSCOEFF7 ; 
 int /*<<< orphan*/  HSCOEFF8 ; 
 int /*<<< orphan*/  SHCTRL ; 
 int /*<<< orphan*/  SHCTRL_HINITIAL ; 
 int /*<<< orphan*/  SPOCTRL ; 
 int SPOCTRL_H_SC_BP ; 
 int SPOCTRL_VORDER_4TAP ; 
 int SPOCTRL_V_SC_BP ; 
 int /*<<< orphan*/  SVCTRL ; 
 int /*<<< orphan*/  SYSCFG ; 
 int /*<<< orphan*/  SYSRST ; 
 int SYSRST_RST ; 
 int Shctrl_Hinitial (int) ; 
 int Svctrl_Initial1 (int) ; 
 int Svctrl_Initial2 (int) ; 
 int /*<<< orphan*/  VSCOEFF0 ; 
 int /*<<< orphan*/  VSCOEFF1 ; 
 int /*<<< orphan*/  VSCOEFF2 ; 
 int /*<<< orphan*/  VSCOEFF3 ; 
 int /*<<< orphan*/  VSCOEFF4 ; 
 int /*<<< orphan*/  enable_clocks (struct fb_info*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_display (struct fb_info*) ; 
 int /*<<< orphan*/  setup_graphics (struct fb_info*) ; 
 int /*<<< orphan*/  setup_memc (struct fb_info*) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dly (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_controller(struct fb_info *fbi)
{
	u32 svctrl, shctrl;

	write_reg_dly(SYSRST_RST, SYSRST);

	/* setup a timeout, raise drive strength */
	write_reg_dly(0xffffff0c, SYSCFG);

	enable_clocks(fbi);
	setup_memc(fbi);
	setup_graphics(fbi);
	setup_display(fbi);

	shctrl = readl(SHCTRL);
	shctrl &= ~(FMsk(SHCTRL_HINITIAL));
	shctrl |= Shctrl_Hinitial(4<<11);
	writel(shctrl, SHCTRL);

	svctrl = Svctrl_Initial1(1<<10) | Svctrl_Initial2(1<<10);
	writel(svctrl, SVCTRL);

	writel(SPOCTRL_H_SC_BP | SPOCTRL_V_SC_BP | SPOCTRL_VORDER_4TAP
			, SPOCTRL);

	/* Those coefficients are good for scaling up. For scaling
	 * down, the application has to calculate them. */
	write_reg(0xff000100, VSCOEFF0);
	write_reg(0xfdfcfdfe, VSCOEFF1);
	write_reg(0x170d0500, VSCOEFF2);
	write_reg(0x3d372d22, VSCOEFF3);
	write_reg(0x00000040, VSCOEFF4);

	write_reg(0xff010100, HSCOEFF0);
	write_reg(0x00000000, HSCOEFF1);
	write_reg(0x02010000, HSCOEFF2);
	write_reg(0x01020302, HSCOEFF3);
	write_reg(0xf9fbfe00, HSCOEFF4);
	write_reg(0xfbf7f6f7, HSCOEFF5);
	write_reg(0x1c110700, HSCOEFF6);
	write_reg(0x3e393127, HSCOEFF7);
	write_reg(0x00000040, HSCOEFF8);

}