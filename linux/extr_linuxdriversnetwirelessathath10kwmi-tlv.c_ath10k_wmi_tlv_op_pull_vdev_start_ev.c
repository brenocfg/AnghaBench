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
struct wmi_vdev_start_response_event {int /*<<< orphan*/  status; int /*<<< orphan*/  resp_type; int /*<<< orphan*/  req_id; int /*<<< orphan*/  vdev_id; } ;
struct wmi_vdev_start_ev_arg {int /*<<< orphan*/  status; int /*<<< orphan*/  resp_type; int /*<<< orphan*/  req_id; int /*<<< orphan*/  vdev_id; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 size_t WMI_TLV_TAG_STRUCT_VDEV_START_RESPONSE_EVENT ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int
ath10k_wmi_tlv_op_pull_vdev_start_ev(struct ath10k *ar, struct sk_buff *skb,
				     struct wmi_vdev_start_ev_arg *arg)
{
	const void **tb;
	const struct wmi_vdev_start_response_event *ev;
	int ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_VDEV_START_RESPONSE_EVENT];
	if (!ev) {
		kfree(tb);
		return -EPROTO;
	}

	skb_pull(skb, sizeof(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->req_id = ev->req_id;
	arg->resp_type = ev->resp_type;
	arg->status = ev->status;

	kfree(tb);
	return 0;
}