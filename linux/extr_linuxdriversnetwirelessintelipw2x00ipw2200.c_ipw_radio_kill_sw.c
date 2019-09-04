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
struct ipw_priv {int status; int /*<<< orphan*/  up; int /*<<< orphan*/  rf_kill; int /*<<< orphan*/  down; int /*<<< orphan*/  scan_event; int /*<<< orphan*/  request_passive_scan; int /*<<< orphan*/  request_direct_scan; int /*<<< orphan*/  request_scan; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_RF_KILL (char*,...) ; 
 int STATUS_RF_KILL_SW ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ rf_kill_active (struct ipw_priv*) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_radio_kill_sw(struct ipw_priv *priv, int disable_radio)
{
	if ((disable_radio ? 1 : 0) ==
	    ((priv->status & STATUS_RF_KILL_SW) ? 1 : 0))
		return 0;

	IPW_DEBUG_RF_KILL("Manual SW RF Kill set to: RADIO  %s\n",
			  disable_radio ? "OFF" : "ON");

	if (disable_radio) {
		priv->status |= STATUS_RF_KILL_SW;

		cancel_delayed_work(&priv->request_scan);
		cancel_delayed_work(&priv->request_direct_scan);
		cancel_delayed_work(&priv->request_passive_scan);
		cancel_delayed_work(&priv->scan_event);
		schedule_work(&priv->down);
	} else {
		priv->status &= ~STATUS_RF_KILL_SW;
		if (rf_kill_active(priv)) {
			IPW_DEBUG_RF_KILL("Can not turn radio back on - "
					  "disabled by HW switch\n");
			/* Make sure the RF_KILL check timer is running */
			cancel_delayed_work(&priv->rf_kill);
			schedule_delayed_work(&priv->rf_kill,
					      round_jiffies_relative(2 * HZ));
		} else
			schedule_work(&priv->up);
	}

	return 1;
}