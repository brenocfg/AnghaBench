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
struct mwifiex_user_scan_cfg {int num_ssids; struct cfg80211_ssid* ssid_list; } ;
struct mwifiex_private {scalar_t__ scan_block; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {scalar_t__ scan_processing; } ;
struct cfg80211_ssid {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN ; 
 int /*<<< orphan*/  kfree (struct mwifiex_user_scan_cfg*) ; 
 struct mwifiex_user_scan_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_scan_networks (struct mwifiex_private*,struct mwifiex_user_scan_cfg*) ; 

__attribute__((used)) static int mwifiex_scan_specific_ssid(struct mwifiex_private *priv,
				      struct cfg80211_ssid *req_ssid)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	int ret;
	struct mwifiex_user_scan_cfg *scan_cfg;

	if (adapter->scan_processing) {
		mwifiex_dbg(adapter, WARN,
			    "cmd: Scan already in process...\n");
		return -EBUSY;
	}

	if (priv->scan_block) {
		mwifiex_dbg(adapter, WARN,
			    "cmd: Scan is blocked during association...\n");
		return -EBUSY;
	}

	scan_cfg = kzalloc(sizeof(struct mwifiex_user_scan_cfg), GFP_KERNEL);
	if (!scan_cfg)
		return -ENOMEM;

	scan_cfg->ssid_list = req_ssid;
	scan_cfg->num_ssids = 1;

	ret = mwifiex_scan_networks(priv, scan_cfg);

	kfree(scan_cfg);
	return ret;
}