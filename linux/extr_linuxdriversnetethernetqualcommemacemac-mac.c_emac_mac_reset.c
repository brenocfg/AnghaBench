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
struct emac_adapter {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EMAC_DMA_MAS_CTRL ; 
 int /*<<< orphan*/  INT_RD_CLR_EN ; 
 int /*<<< orphan*/  SOFT_RST ; 
 int /*<<< orphan*/  emac_mac_stop (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_reg_update32 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void emac_mac_reset(struct emac_adapter *adpt)
{
	emac_mac_stop(adpt);

	emac_reg_update32(adpt->base + EMAC_DMA_MAS_CTRL, 0, SOFT_RST);
	usleep_range(100, 150); /* reset may take up to 100usec */

	/* interrupt clear-on-read */
	emac_reg_update32(adpt->base + EMAC_DMA_MAS_CTRL, 0, INT_RD_CLR_EN);
}