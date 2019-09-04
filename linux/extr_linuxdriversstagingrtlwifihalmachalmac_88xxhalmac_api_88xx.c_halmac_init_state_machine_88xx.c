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
struct halmac_state {int /*<<< orphan*/  ps_state; int /*<<< orphan*/  mac_power; int /*<<< orphan*/  dlfw_state; int /*<<< orphan*/  api_state; } ;
struct halmac_adapter {struct halmac_state halmac_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_API_STATE_INIT ; 
 int /*<<< orphan*/  HALMAC_DLFW_NONE ; 
 int /*<<< orphan*/  HALMAC_MAC_POWER_OFF ; 
 int /*<<< orphan*/  HALMAC_PS_STATE_UNDEFINE ; 
 int /*<<< orphan*/  halmac_init_offload_feature_state_machine_88xx (struct halmac_adapter*) ; 

void halmac_init_state_machine_88xx(struct halmac_adapter *halmac_adapter)
{
	struct halmac_state *state = &halmac_adapter->halmac_state;

	halmac_init_offload_feature_state_machine_88xx(halmac_adapter);

	state->api_state = HALMAC_API_STATE_INIT;

	state->dlfw_state = HALMAC_DLFW_NONE;
	state->mac_power = HALMAC_MAC_POWER_OFF;
	state->ps_state = HALMAC_PS_STATE_UNDEFINE;
}