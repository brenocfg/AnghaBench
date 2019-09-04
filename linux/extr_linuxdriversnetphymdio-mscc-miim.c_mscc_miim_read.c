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
struct mscc_miim_dev {scalar_t__ regs; } ;
struct mii_bus {struct mscc_miim_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int MSCC_MIIM_CMD_OPR_READ ; 
 int MSCC_MIIM_CMD_PHYAD_SHIFT ; 
 int MSCC_MIIM_CMD_REGAD_SHIFT ; 
 int MSCC_MIIM_CMD_VLD ; 
 int MSCC_MIIM_DATA_ERROR ; 
 scalar_t__ MSCC_MIIM_REG_CMD ; 
 scalar_t__ MSCC_MIIM_REG_DATA ; 
 int mscc_miim_wait_ready (struct mii_bus*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mscc_miim_read(struct mii_bus *bus, int mii_id, int regnum)
{
	struct mscc_miim_dev *miim = bus->priv;
	u32 val;
	int ret;

	ret = mscc_miim_wait_ready(bus);
	if (ret)
		goto out;

	writel(MSCC_MIIM_CMD_VLD | (mii_id << MSCC_MIIM_CMD_PHYAD_SHIFT) |
	       (regnum << MSCC_MIIM_CMD_REGAD_SHIFT) | MSCC_MIIM_CMD_OPR_READ,
	       miim->regs + MSCC_MIIM_REG_CMD);

	ret = mscc_miim_wait_ready(bus);
	if (ret)
		goto out;

	val = readl(miim->regs + MSCC_MIIM_REG_DATA);
	if (val & MSCC_MIIM_DATA_ERROR) {
		ret = -EIO;
		goto out;
	}

	ret = val & 0xFFFF;
out:
	return ret;
}