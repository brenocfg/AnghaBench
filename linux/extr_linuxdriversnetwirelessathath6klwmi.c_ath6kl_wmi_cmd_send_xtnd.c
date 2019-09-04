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
struct wmix_cmd_hdr {int /*<<< orphan*/  cmd_id; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum wmix_command_id { ____Placeholder_wmix_command_id } wmix_command_id ;
typedef  enum wmi_sync_flag { ____Placeholder_wmi_sync_flag } wmi_sync_flag ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_EXTENSION_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int ath6kl_wmi_cmd_send_xtnd(struct wmi *wmi, struct sk_buff *skb,
				    enum wmix_command_id cmd_id,
				    enum wmi_sync_flag sync_flag)
{
	struct wmix_cmd_hdr *cmd_hdr;
	int ret;

	skb_push(skb, sizeof(struct wmix_cmd_hdr));

	cmd_hdr = (struct wmix_cmd_hdr *) skb->data;
	cmd_hdr->cmd_id = cpu_to_le32(cmd_id);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_EXTENSION_CMDID, sync_flag);

	return ret;
}