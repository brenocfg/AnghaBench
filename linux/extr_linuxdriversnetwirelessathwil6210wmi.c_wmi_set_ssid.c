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
typedef  int u8 ;
struct wmi_set_ssid_cmd {int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WMI_SET_SSID_CMDID ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_set_ssid_cmd*,int) ; 

int wmi_set_ssid(struct wil6210_vif *vif, u8 ssid_len, const void *ssid)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wmi_set_ssid_cmd cmd = {
		.ssid_len = cpu_to_le32(ssid_len),
	};

	if (ssid_len > sizeof(cmd.ssid))
		return -EINVAL;

	memcpy(cmd.ssid, ssid, ssid_len);

	return wmi_send(wil, WMI_SET_SSID_CMDID, vif->mid, &cmd, sizeof(cmd));
}