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
struct ath6kl_vif {int /*<<< orphan*/  flags; int /*<<< orphan*/  fw_vif_idx; TYPE_1__* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  CONNECT_PEND ; 
 int /*<<< orphan*/  ath6kl_wmi_disconnect_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_disconnect(struct ath6kl_vif *vif)
{
	if (test_bit(CONNECTED, &vif->flags) ||
	    test_bit(CONNECT_PEND, &vif->flags)) {
		ath6kl_wmi_disconnect_cmd(vif->ar->wmi, vif->fw_vif_idx);
		/*
		 * Disconnect command is issued, clear the connect pending
		 * flag. The connected flag will be cleared in
		 * disconnect event notification.
		 */
		clear_bit(CONNECT_PEND, &vif->flags);
	}
}