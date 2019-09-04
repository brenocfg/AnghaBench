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
struct wmi_scan_event {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  scan_id; int /*<<< orphan*/  scan_req_id; int /*<<< orphan*/  channel_freq; int /*<<< orphan*/  reason; int /*<<< orphan*/  event_type; } ;
struct wmi_scan_ev_arg {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  scan_id; int /*<<< orphan*/  scan_req_id; int /*<<< orphan*/  channel_freq; int /*<<< orphan*/  reason; int /*<<< orphan*/  event_type; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 size_t WMI_TLV_TAG_STRUCT_SCAN_EVENT ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_scan_ev(struct ath10k *ar,
					  struct sk_buff *skb,
					  struct wmi_scan_ev_arg *arg)
{
	const void **tb;
	const struct wmi_scan_event *ev;
	int ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_SCAN_EVENT];
	if (!ev) {
		kfree(tb);
		return -EPROTO;
	}

	arg->event_type = ev->event_type;
	arg->reason = ev->reason;
	arg->channel_freq = ev->channel_freq;
	arg->scan_req_id = ev->scan_req_id;
	arg->scan_id = ev->scan_id;
	arg->vdev_id = ev->vdev_id;

	kfree(tb);
	return 0;
}