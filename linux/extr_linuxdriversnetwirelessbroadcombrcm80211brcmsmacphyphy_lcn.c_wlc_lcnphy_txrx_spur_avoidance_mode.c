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
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlapi_switch_macfreq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_lcnphy_txrx_spur_avoidance_mode(struct brcms_phy *pi, bool enable)
{
	if (enable) {
		write_phy_reg(pi, 0x942, 0x7);
		write_phy_reg(pi, 0x93b, ((1 << 13) + 23));
		write_phy_reg(pi, 0x93c, ((1 << 13) + 1989));

		write_phy_reg(pi, 0x44a, 0x084);
		write_phy_reg(pi, 0x44a, 0x080);
		write_phy_reg(pi, 0x6d3, 0x2222);
		write_phy_reg(pi, 0x6d3, 0x2220);
	} else {
		write_phy_reg(pi, 0x942, 0x0);
		write_phy_reg(pi, 0x93b, ((0 << 13) + 23));
		write_phy_reg(pi, 0x93c, ((0 << 13) + 1989));
	}
	wlapi_switch_macfreq(pi->sh->physhim, enable);
}