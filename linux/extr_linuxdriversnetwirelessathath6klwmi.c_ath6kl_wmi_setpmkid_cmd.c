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
struct wmi_setpmkid_cmd {int /*<<< orphan*/  enable; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  PMKID_DISABLE ; 
 int /*<<< orphan*/  PMKID_ENABLE ; 
 int /*<<< orphan*/  WMI_SET_PMKID_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ath6kl_wmi_setpmkid_cmd(struct wmi *wmi, u8 if_idx, const u8 *bssid,
			    const u8 *pmkid, bool set)
{
	struct sk_buff *skb;
	struct wmi_setpmkid_cmd *cmd;
	int ret;

	if (bssid == NULL)
		return -EINVAL;

	if (set && pmkid == NULL)
		return -EINVAL;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_setpmkid_cmd *) skb->data;
	memcpy(cmd->bssid, bssid, ETH_ALEN);
	if (set) {
		memcpy(cmd->pmkid, pmkid, sizeof(cmd->pmkid));
		cmd->enable = PMKID_ENABLE;
	} else {
		memset(cmd->pmkid, 0, sizeof(cmd->pmkid));
		cmd->enable = PMKID_DISABLE;
	}

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_PMKID_CMDID,
				  NO_SYNC_WMIFLAG);

	return ret;
}