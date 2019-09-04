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
 int ETIMEDOUT ; 
 scalar_t__ MSCC_MIIM_REG_STATUS ; 
 int MSCC_MIIM_STATUS_STAT_BUSY ; 
 int /*<<< orphan*/  readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int mscc_miim_wait_ready(struct mii_bus *bus)
{
	struct mscc_miim_dev *miim = bus->priv;
	u32 val;

	readl_poll_timeout(miim->regs + MSCC_MIIM_REG_STATUS, val,
			   !(val & MSCC_MIIM_STATUS_STAT_BUSY), 100, 250000);
	if (val & MSCC_MIIM_STATUS_STAT_BUSY)
		return -ETIMEDOUT;

	return 0;
}