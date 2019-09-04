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
typedef  int /*<<< orphan*/  u32 ;
struct isci_phy {int /*<<< orphan*/  protocol; int /*<<< orphan*/  sm; TYPE_1__* link_layer_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_configuration; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_PROTOCOL_SSP ; 
 int /*<<< orphan*/  SATA_SPINUP_HOLD ; 
 int /*<<< orphan*/  SCI_PHY_SUB_AWAIT_SAS_SPEED_EN ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_phy_start_sas_link_training(struct isci_phy *iphy)
{
	/* continue the link training for the phy as if it were a SAS PHY
	 * instead of a SATA PHY. This is done because the completion queue had a SAS
	 * PHY DETECTED event when the state machine was expecting a SATA PHY event.
	 */
	u32 phy_control;

	phy_control = readl(&iphy->link_layer_registers->phy_configuration);
	phy_control |= SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOLD);
	writel(phy_control,
	       &iphy->link_layer_registers->phy_configuration);

	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SAS_SPEED_EN);

	iphy->protocol = SAS_PROTOCOL_SSP;
}