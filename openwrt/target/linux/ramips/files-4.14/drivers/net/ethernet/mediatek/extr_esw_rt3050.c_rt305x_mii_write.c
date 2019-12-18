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
struct rt305x_esw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RT305X_ESW_PCR0_CPU_PHY_REG_S ; 
 int RT305X_ESW_PCR0_WT_NWAY_DATA_S ; 
 int RT305X_ESW_PCR0_WT_PHY_CMD ; 
 int RT305X_ESW_PCR1_WT_DONE ; 
 scalar_t__ RT305X_ESW_PHY_TIMEOUT ; 
 int /*<<< orphan*/  RT305X_ESW_REG_PCR0 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_PCR1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int esw_r32 (struct rt305x_esw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_w32 (struct rt305x_esw*,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static u32 rt305x_mii_write(struct rt305x_esw *esw, u32 phy_addr,
			    u32 phy_register, u32 write_data)
{
	unsigned long t_start = jiffies;
	int ret = 0;

	while (1) {
		if (!(esw_r32(esw, RT305X_ESW_REG_PCR1) &
		      RT305X_ESW_PCR1_WT_DONE))
			break;
		if (time_after(jiffies, t_start + RT305X_ESW_PHY_TIMEOUT)) {
			ret = 1;
			goto out;
		}
	}

	write_data &= 0xffff;
	esw_w32(esw, (write_data << RT305X_ESW_PCR0_WT_NWAY_DATA_S) |
		      (phy_register << RT305X_ESW_PCR0_CPU_PHY_REG_S) |
		      (phy_addr) | RT305X_ESW_PCR0_WT_PHY_CMD,
		RT305X_ESW_REG_PCR0);

	t_start = jiffies;
	while (1) {
		if (esw_r32(esw, RT305X_ESW_REG_PCR1) &
			    RT305X_ESW_PCR1_WT_DONE)
			break;

		if (time_after(jiffies, t_start + RT305X_ESW_PHY_TIMEOUT)) {
			ret = 1;
			break;
		}
	}
out:
	if (ret)
		dev_err(esw->dev, "ramips_eth: MDIO timeout\n");
	return ret;
}