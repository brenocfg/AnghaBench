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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct mwifiex_private {scalar_t__ usb_port; struct mwifiex_adapter* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct mwifiex_ie_types_multi_chan_info {scalar_t__ tlv_buffer; int /*<<< orphan*/  status; TYPE_1__ header; } ;
struct TYPE_4__ {scalar_t__ usb_ep_num; } ;
struct mwifiex_ie_types_mc_group_info {int intf_num; int* bss_type_numlist; TYPE_2__ hid_num; } ;
struct mwifiex_ie_types_header {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct mwifiex_adapter {scalar_t__ iface_type; int tx_lock_flag; int usb_mc_setup; scalar_t__ usb_mc_status; } ;

/* Variables and functions */
 int BSS_NUM_MASK ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVENT ; 
 scalar_t__ MWIFIEX_USB ; 
 scalar_t__ MWIFIEX_USB_EP_DATA ; 
 scalar_t__ MWIFIEX_USB_EP_DATA_CH2 ; 
 int TLV_TYPE_MC_GROUP_INFO ; 
 scalar_t__ TLV_TYPE_MULTI_CHAN_INFO ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 struct mwifiex_private* mwifiex_get_priv_by_id (struct mwifiex_adapter*,int,int) ; 
 int /*<<< orphan*/  mwifiex_multi_chan_resync (struct mwifiex_adapter*) ; 

void mwifiex_process_multi_chan_event(struct mwifiex_private *priv,
				      struct sk_buff *event_skb)
{
	struct mwifiex_ie_types_multi_chan_info *chan_info;
	struct mwifiex_ie_types_mc_group_info *grp_info;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_ie_types_header *tlv;
	u16 tlv_buf_left, tlv_type, tlv_len;
	int intf_num, bss_type, bss_num, i;
	struct mwifiex_private *intf_priv;

	tlv_buf_left = event_skb->len - sizeof(u32);
	chan_info = (void *)event_skb->data + sizeof(u32);

	if (le16_to_cpu(chan_info->header.type) != TLV_TYPE_MULTI_CHAN_INFO ||
	    tlv_buf_left < sizeof(struct mwifiex_ie_types_multi_chan_info)) {
		mwifiex_dbg(adapter, ERROR,
			    "unknown TLV in chan_info event\n");
		return;
	}

	adapter->usb_mc_status = le16_to_cpu(chan_info->status);
	mwifiex_dbg(adapter, EVENT, "multi chan operation %s\n",
		    adapter->usb_mc_status ? "started" : "over");

	tlv_buf_left -= sizeof(struct mwifiex_ie_types_multi_chan_info);
	tlv = (struct mwifiex_ie_types_header *)chan_info->tlv_buffer;

	while (tlv_buf_left >= (int)sizeof(struct mwifiex_ie_types_header)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_len  = le16_to_cpu(tlv->len);
		if ((sizeof(struct mwifiex_ie_types_header) + tlv_len) >
		    tlv_buf_left) {
			mwifiex_dbg(adapter, ERROR, "wrong tlv: tlvLen=%d,\t"
				    "tlvBufLeft=%d\n", tlv_len, tlv_buf_left);
			break;
		}
		if (tlv_type != TLV_TYPE_MC_GROUP_INFO) {
			mwifiex_dbg(adapter, ERROR, "wrong tlv type: 0x%x\n",
				    tlv_type);
			break;
		}

		grp_info = (struct mwifiex_ie_types_mc_group_info *)tlv;
		intf_num = grp_info->intf_num;
		for (i = 0; i < intf_num; i++) {
			bss_type = grp_info->bss_type_numlist[i] >> 4;
			bss_num = grp_info->bss_type_numlist[i] & BSS_NUM_MASK;
			intf_priv = mwifiex_get_priv_by_id(adapter, bss_num,
							   bss_type);
			if (!intf_priv) {
				mwifiex_dbg(adapter, ERROR,
					    "Invalid bss_type bss_num\t"
					    "in multi channel event\n");
				continue;
			}
			if (adapter->iface_type == MWIFIEX_USB) {
				u8 ep;

				ep = grp_info->hid_num.usb_ep_num;
				if (ep == MWIFIEX_USB_EP_DATA ||
				    ep == MWIFIEX_USB_EP_DATA_CH2)
					intf_priv->usb_port = ep;
			}
		}

		tlv_buf_left -= sizeof(struct mwifiex_ie_types_header) +
				tlv_len;
		tlv = (void *)((u8 *)tlv + tlv_len +
			       sizeof(struct mwifiex_ie_types_header));
	}

	if (adapter->iface_type == MWIFIEX_USB) {
		adapter->tx_lock_flag = true;
		adapter->usb_mc_setup = true;
		mwifiex_multi_chan_resync(adapter);
	}
}