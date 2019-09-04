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
struct wmi_new_sta_cmd {int /*<<< orphan*/  dst_mac; int /*<<< orphan*/  aid; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_NEW_STA_CMDID ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_new_sta_cmd*,int) ; 

int wmi_new_sta(struct wil6210_vif *vif, const u8 *mac, u8 aid)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	int rc;
	struct wmi_new_sta_cmd cmd = {
		.aid = aid,
	};

	wil_dbg_wmi(wil, "new sta %pM, aid %d\n", mac, aid);

	ether_addr_copy(cmd.dst_mac, mac);

	rc = wmi_send(wil, WMI_NEW_STA_CMDID, vif->mid, &cmd, sizeof(cmd));
	if (rc)
		wil_err(wil, "Failed to send new sta (%d)\n", rc);

	return rc;
}