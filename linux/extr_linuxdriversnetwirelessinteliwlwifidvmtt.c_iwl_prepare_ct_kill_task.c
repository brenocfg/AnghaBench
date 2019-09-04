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
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_waiting_tm; } ;
struct iwl_priv {TYPE_1__ thermal_throttle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_KILL_WAITING_DURATION ; 
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  iwl_send_statistics_request (struct iwl_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_prepare_ct_kill_task(struct iwl_priv *priv)
{
	IWL_DEBUG_TEMP(priv, "Prepare to enter IWL_TI_CT_KILL\n");
	/* make request to retrieve statistics information */
	iwl_send_statistics_request(priv, 0, false);
	/* Reschedule the ct_kill wait timer */
	mod_timer(&priv->thermal_throttle.ct_kill_waiting_tm,
		 jiffies + msecs_to_jiffies(CT_KILL_WAITING_DURATION));
}