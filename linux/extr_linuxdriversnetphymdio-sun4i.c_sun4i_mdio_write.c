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
struct sun4i_mdio_data {scalar_t__ membase; } ;
struct mii_bus {struct sun4i_mdio_data* priv; } ;

/* Variables and functions */
 scalar_t__ EMAC_MAC_MADR_REG ; 
 scalar_t__ EMAC_MAC_MCMD_REG ; 
 scalar_t__ EMAC_MAC_MIND_REG ; 
 scalar_t__ EMAC_MAC_MWTD_REG ; 
 int ETIMEDOUT ; 
 unsigned long MDIO_TIMEOUT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
			    u16 value)
{
	struct sun4i_mdio_data *data = bus->priv;
	unsigned long timeout_jiffies;

	/* issue the phy address and reg */
	writel((mii_id << 8) | regnum, data->membase + EMAC_MAC_MADR_REG);
	/* pull up the phy io line */
	writel(0x1, data->membase + EMAC_MAC_MCMD_REG);

	/* Wait read complete */
	timeout_jiffies = jiffies + MDIO_TIMEOUT;
	while (readl(data->membase + EMAC_MAC_MIND_REG) & 0x1) {
		if (time_is_before_jiffies(timeout_jiffies))
			return -ETIMEDOUT;
		msleep(1);
	}

	/* push down the phy io line */
	writel(0x0, data->membase + EMAC_MAC_MCMD_REG);
	/* and write data */
	writel(value, data->membase + EMAC_MAC_MWTD_REG);

	return 0;
}