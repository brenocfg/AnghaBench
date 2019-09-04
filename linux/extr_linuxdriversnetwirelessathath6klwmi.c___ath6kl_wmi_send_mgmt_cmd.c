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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct wmi_send_mgmt_cmd {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; void* no_cck; void* wait; void* freq; void* id; } ;
struct wmi {scalar_t__ last_mgmt_tx_frame_len; int /*<<< orphan*/ * last_mgmt_tx_frame; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SEND_MGMT_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int __ath6kl_wmi_send_mgmt_cmd(struct wmi *wmi, u8 if_idx, u32 id,
				      u32 freq, u32 wait, const u8 *data,
				      u16 data_len, u32 no_cck)
{
	struct sk_buff *skb;
	struct wmi_send_mgmt_cmd *p;
	u8 *buf;

	if (wait)
		return -EINVAL; /* Offload for wait not supported */

	buf = kmalloc(data_len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	skb = ath6kl_wmi_get_new_buf(sizeof(*p) + data_len);
	if (!skb) {
		kfree(buf);
		return -ENOMEM;
	}

	kfree(wmi->last_mgmt_tx_frame);
	memcpy(buf, data, data_len);
	wmi->last_mgmt_tx_frame = buf;
	wmi->last_mgmt_tx_frame_len = data_len;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "send_action_cmd: id=%u freq=%u wait=%u len=%u\n",
		   id, freq, wait, data_len);
	p = (struct wmi_send_mgmt_cmd *) skb->data;
	p->id = cpu_to_le32(id);
	p->freq = cpu_to_le32(freq);
	p->wait = cpu_to_le32(wait);
	p->no_cck = cpu_to_le32(no_cck);
	p->len = cpu_to_le16(data_len);
	memcpy(p->data, data, data_len);
	return ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SEND_MGMT_CMDID,
				   NO_SYNC_WMIFLAG);
}