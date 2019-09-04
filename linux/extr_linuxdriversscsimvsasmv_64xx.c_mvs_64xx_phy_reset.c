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
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int MVS_HARD_RESET ; 
 int MVS_SOFT_RESET ; 
 int PHYEV_RDY_CH ; 
 int PHY_RST ; 
 int PHY_RST_HARD ; 
 int mvs_read_phy_ctl (struct mvs_info*,int) ; 
 int mvs_read_port_irq_stat (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_phy_ctl (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  mvs_write_port_irq_stat (struct mvs_info*,int,int) ; 

__attribute__((used)) static void mvs_64xx_phy_reset(struct mvs_info *mvi, u32 phy_id, int hard)
{
	u32 tmp;
	tmp = mvs_read_port_irq_stat(mvi, phy_id);
	tmp &= ~PHYEV_RDY_CH;
	mvs_write_port_irq_stat(mvi, phy_id, tmp);
	tmp = mvs_read_phy_ctl(mvi, phy_id);
	if (hard == MVS_HARD_RESET)
		tmp |= PHY_RST_HARD;
	else if (hard == MVS_SOFT_RESET)
		tmp |= PHY_RST;
	mvs_write_phy_ctl(mvi, phy_id, tmp);
	if (hard) {
		do {
			tmp = mvs_read_phy_ctl(mvi, phy_id);
		} while (tmp & PHY_RST_HARD);
	}
}