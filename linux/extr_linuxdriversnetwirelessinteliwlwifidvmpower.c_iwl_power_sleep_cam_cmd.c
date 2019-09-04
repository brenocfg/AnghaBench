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
struct TYPE_2__ {scalar_t__ bus_pm; } ;
struct iwl_priv {TYPE_1__ power_data; } ;
struct iwl_powertable_cmd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_POWER_PCI_PM_MSK ; 
 int /*<<< orphan*/  memset (struct iwl_powertable_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_power_sleep_cam_cmd(struct iwl_priv *priv,
				    struct iwl_powertable_cmd *cmd)
{
	memset(cmd, 0, sizeof(*cmd));

	if (priv->power_data.bus_pm)
		cmd->flags |= IWL_POWER_PCI_PM_MSK;

	IWL_DEBUG_POWER(priv, "Sleep command for CAM\n");
}