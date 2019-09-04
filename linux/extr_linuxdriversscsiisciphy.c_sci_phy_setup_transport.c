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
struct isci_phy {TYPE_1__* transport_layer_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  stp_rni; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_TCI_NCQ_MAPPING_TABLE ; 
 int /*<<< orphan*/  SCU_TLCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sci_phy_setup_transport(struct isci_phy *iphy, u32 device_id)
{
	u32 tl_control;

	writel(device_id, &iphy->transport_layer_registers->stp_rni);

	/*
	 * The read should guarantee that the first write gets posted
	 * before the next write
	 */
	tl_control = readl(&iphy->transport_layer_registers->control);
	tl_control |= SCU_TLCR_GEN_BIT(CLEAR_TCI_NCQ_MAPPING_TABLE);
	writel(tl_control, &iphy->transport_layer_registers->control);
}