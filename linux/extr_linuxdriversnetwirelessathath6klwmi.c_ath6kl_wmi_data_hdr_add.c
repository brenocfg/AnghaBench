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
typedef  int u8 ;
typedef  int u32 ;
struct wmi_data_hdr {int info; int /*<<< orphan*/  info3; int /*<<< orphan*/  info2; } ;
struct wmi {TYPE_1__* parent_dev; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum wmi_data_hdr_data_type { ____Placeholder_wmi_data_hdr_data_type } wmi_data_hdr_data_type ;
struct TYPE_2__ {int vif_max; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int WMI_DATA_HDR_DATA_TYPE_SHIFT ; 
 int WMI_DATA_HDR_EOSP ; 
 int WMI_DATA_HDR_FLAGS_EOSP ; 
 int WMI_DATA_HDR_FLAGS_MORE ; 
 int WMI_DATA_HDR_IF_IDX_MASK ; 
 int WMI_DATA_HDR_META_SHIFT ; 
 int WMI_DATA_HDR_MORE ; 
 int WMI_DATA_HDR_MSG_TYPE_SHIFT ; 
 int ath6kl_wmi_meta_add (struct wmi*,struct sk_buff*,int*,void*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct wmi_data_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

int ath6kl_wmi_data_hdr_add(struct wmi *wmi, struct sk_buff *skb,
			    u8 msg_type, u32 flags,
			    enum wmi_data_hdr_data_type data_type,
			    u8 meta_ver, void *tx_meta_info, u8 if_idx)
{
	struct wmi_data_hdr *data_hdr;
	int ret;

	if (WARN_ON(skb == NULL || (if_idx > wmi->parent_dev->vif_max - 1)))
		return -EINVAL;

	if (tx_meta_info) {
		ret = ath6kl_wmi_meta_add(wmi, skb, &meta_ver, tx_meta_info);
		if (ret)
			return ret;
	}

	skb_push(skb, sizeof(struct wmi_data_hdr));

	data_hdr = (struct wmi_data_hdr *)skb->data;
	memset(data_hdr, 0, sizeof(struct wmi_data_hdr));

	data_hdr->info = msg_type << WMI_DATA_HDR_MSG_TYPE_SHIFT;
	data_hdr->info |= data_type << WMI_DATA_HDR_DATA_TYPE_SHIFT;

	if (flags & WMI_DATA_HDR_FLAGS_MORE)
		data_hdr->info |= WMI_DATA_HDR_MORE;

	if (flags & WMI_DATA_HDR_FLAGS_EOSP)
		data_hdr->info3 |= cpu_to_le16(WMI_DATA_HDR_EOSP);

	data_hdr->info2 |= cpu_to_le16(meta_ver << WMI_DATA_HDR_META_SHIFT);
	data_hdr->info3 |= cpu_to_le16(if_idx & WMI_DATA_HDR_IF_IDX_MASK);

	return 0;
}