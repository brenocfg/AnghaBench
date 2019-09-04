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
struct wmi {struct ath6kl* parent_dev; } ;
struct ath6kl_vif {int /*<<< orphan*/  flags; } ;
struct ath6kl {int /*<<< orphan*/  event_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_SLEEP_MODE_CMD_PROCESSED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_wmi_host_sleep_mode_cmd_prcd_evt_rx(struct wmi *wmi,
						      struct ath6kl_vif *vif)
{
	struct ath6kl *ar = wmi->parent_dev;

	set_bit(HOST_SLEEP_MODE_CMD_PROCESSED, &vif->flags);
	wake_up(&ar->event_wq);

	return 0;
}