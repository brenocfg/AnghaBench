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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_toggle_afe_pwdn(struct brcms_phy *pi)
{
	u16 save_AfeCtrlOvrVal, save_AfeCtrlOvr;

	save_AfeCtrlOvrVal = read_phy_reg(pi, 0x43c);
	save_AfeCtrlOvr = read_phy_reg(pi, 0x43b);

	write_phy_reg(pi, 0x43c, save_AfeCtrlOvrVal | 0x1);
	write_phy_reg(pi, 0x43b, save_AfeCtrlOvr | 0x1);

	write_phy_reg(pi, 0x43c, save_AfeCtrlOvrVal & 0xfffe);
	write_phy_reg(pi, 0x43b, save_AfeCtrlOvr & 0xfffe);

	write_phy_reg(pi, 0x43c, save_AfeCtrlOvrVal);
	write_phy_reg(pi, 0x43b, save_AfeCtrlOvr);
}