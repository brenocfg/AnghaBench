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
struct stmmac_priv {int ioaddr; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int readl (int) ; 

__attribute__((used)) static u32 stmmac_get_id(struct stmmac_priv *priv, u32 id_reg)
{
	u32 reg = readl(priv->ioaddr + id_reg);

	if (!reg) {
		dev_info(priv->device, "Version ID not available\n");
		return 0x0;
	}

	dev_info(priv->device, "User ID: 0x%x, Synopsys ID: 0x%x\n",
			(unsigned int)(reg & GENMASK(15, 8)) >> 8,
			(unsigned int)(reg & GENMASK(7, 0)));
	return reg & GENMASK(7, 0);
}