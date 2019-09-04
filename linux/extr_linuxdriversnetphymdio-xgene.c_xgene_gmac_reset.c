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
struct xgene_mdio_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CONFIG_1_ADDR ; 
 int /*<<< orphan*/  SOFT_RESET ; 
 int /*<<< orphan*/  xgene_mdio_wr_mac (struct xgene_mdio_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_gmac_reset(struct xgene_mdio_pdata *pdata)
{
	xgene_mdio_wr_mac(pdata, MAC_CONFIG_1_ADDR, SOFT_RESET);
	xgene_mdio_wr_mac(pdata, MAC_CONFIG_1_ADDR, 0);
}