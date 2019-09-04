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
struct stmmac_priv {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  device; struct mac_device_info* hw; } ;
struct TYPE_4__ {int addr_shift; int addr_mask; int reg_shift; int reg_mask; int clk_csr_shift; int /*<<< orphan*/  clk_csr_mask; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed_mask; scalar_t__ speed1000; scalar_t__ speed100; scalar_t__ speed10; int /*<<< orphan*/  duplex; } ;
struct mac_device_info {TYPE_2__ mii; TYPE_1__ link; int /*<<< orphan*/  pcsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  MAC_CONTROL_F ; 
 int /*<<< orphan*/  MAC_CONTROL_PS ; 
 int /*<<< orphan*/  MAC_MII_ADDR ; 
 int /*<<< orphan*/  MAC_MII_DATA ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

int dwmac100_setup(struct stmmac_priv *priv)
{
	struct mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tDWMAC100\n");

	mac->pcsr = priv->ioaddr;
	mac->link.duplex = MAC_CONTROL_F;
	mac->link.speed10 = 0;
	mac->link.speed100 = 0;
	mac->link.speed1000 = 0;
	mac->link.speed_mask = MAC_CONTROL_PS;
	mac->mii.addr = MAC_MII_ADDR;
	mac->mii.data = MAC_MII_DATA;
	mac->mii.addr_shift = 11;
	mac->mii.addr_mask = 0x0000F800;
	mac->mii.reg_shift = 6;
	mac->mii.reg_mask = 0x000007C0;
	mac->mii.clk_csr_shift = 2;
	mac->mii.clk_csr_mask = GENMASK(5, 2);

	return 0;
}