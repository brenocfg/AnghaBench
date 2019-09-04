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
typedef  int u16 ;
struct brcms_phy_lcnphy {int lcnphy_rssi_vf; int lcnphy_rssi_vc; int lcnphy_rssi_gs; } ;
struct TYPE_3__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_2__* sh; TYPE_1__ u; } ;
struct TYPE_4__ {int boardflags; } ;

/* Variables and functions */
 int BFL_FEM ; 
 int /*<<< orphan*/  RADIO_2064_REG11C ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wlc_lcnphy_rev0_baseband_init(struct brcms_phy *pi)
{
	u16 afectrl1;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	write_radio_reg(pi, RADIO_2064_REG11C, 0x0);

	write_phy_reg(pi, 0x43b, 0x0);
	write_phy_reg(pi, 0x43c, 0x0);
	write_phy_reg(pi, 0x44c, 0x0);
	write_phy_reg(pi, 0x4e6, 0x0);
	write_phy_reg(pi, 0x4f9, 0x0);
	write_phy_reg(pi, 0x4b0, 0x0);
	write_phy_reg(pi, 0x938, 0x0);
	write_phy_reg(pi, 0x4b0, 0x0);
	write_phy_reg(pi, 0x44e, 0);

	or_phy_reg(pi, 0x567, 0x03);

	or_phy_reg(pi, 0x44a, 0x44);
	write_phy_reg(pi, 0x44a, 0x80);

	if (!(pi->sh->boardflags & BFL_FEM))
		wlc_lcnphy_set_tx_pwr_by_index(pi, 52);

	if (0) {
		afectrl1 = 0;
		afectrl1 = (u16) ((pi_lcn->lcnphy_rssi_vf) |
				  (pi_lcn->lcnphy_rssi_vc << 4) |
				  (pi_lcn->lcnphy_rssi_gs << 10));
		write_phy_reg(pi, 0x43e, afectrl1);
	}

	mod_phy_reg(pi, 0x634, (0xff << 0), 0xC << 0);
	if (pi->sh->boardflags & BFL_FEM) {
		mod_phy_reg(pi, 0x634, (0xff << 0), 0xA << 0);

		write_phy_reg(pi, 0x910, 0x1);
	}

	mod_phy_reg(pi, 0x448, (0x3 << 8), 1 << 8);
	mod_phy_reg(pi, 0x608, (0xff << 0), 0x17 << 0);
	mod_phy_reg(pi, 0x604, (0x7ff << 0), 0x3EA << 0);

}