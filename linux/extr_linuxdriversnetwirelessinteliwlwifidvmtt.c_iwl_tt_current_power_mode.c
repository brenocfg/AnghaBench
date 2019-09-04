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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_tt_mgmt {int /*<<< orphan*/  tt_power_mode; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; } ;

/* Variables and functions */

u8 iwl_tt_current_power_mode(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;

	return tt->tt_power_mode;
}