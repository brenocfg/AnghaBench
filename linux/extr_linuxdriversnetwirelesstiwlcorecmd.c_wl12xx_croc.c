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
struct wl1271 {int /*<<< orphan*/  roc_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_MAX_ROLES ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl12xx_cmd_croc (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl12xx_rearm_tx_watchdog_locked (struct wl1271*) ; 

int wl12xx_croc(struct wl1271 *wl, u8 role_id)
{
	int ret = 0;

	if (WARN_ON(!test_bit(role_id, wl->roc_map)))
		return 0;

	ret = wl12xx_cmd_croc(wl, role_id);
	if (ret < 0)
		goto out;

	__clear_bit(role_id, wl->roc_map);

	/*
	 * Rearm the tx watchdog when removing the last ROC. This prevents
	 * recoveries due to just finished ROCs - when Tx hasn't yet had
	 * a chance to get out.
	 */
	if (find_first_bit(wl->roc_map, WL12XX_MAX_ROLES) >= WL12XX_MAX_ROLES)
		wl12xx_rearm_tx_watchdog_locked(wl);
out:
	return ret;
}