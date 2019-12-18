#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ mlme; } ;
struct ieee80211_event {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEAUTH_RX_EVENT ; 
 int /*<<< orphan*/  DEAUTH_TX_EVENT ; 
 int /*<<< orphan*/  MLME_EVENT ; 
 int /*<<< orphan*/  cfg80211_rx_mlme_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cfg80211_tx_mlme_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  drv_event_callback (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,struct ieee80211_event*) ; 

__attribute__((used)) static void ieee80211_report_disconnect(struct ieee80211_sub_if_data *sdata,
					const u8 *buf, size_t len, bool tx,
					u16 reason)
{
	struct ieee80211_event event = {
		.type = MLME_EVENT,
		.u.mlme.data = tx ? DEAUTH_TX_EVENT : DEAUTH_RX_EVENT,
		.u.mlme.reason = reason,
	};

	if (tx)
		cfg80211_tx_mlme_mgmt(sdata->dev, buf, len);
	else
		cfg80211_rx_mlme_mgmt(sdata->dev, buf, len);

	drv_event_callback(sdata->local, sdata, &event);
}