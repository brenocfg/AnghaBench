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
struct wmi_tlv_phyerr_ev {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  tsf_u32; int /*<<< orphan*/  tsf_l32; int /*<<< orphan*/  num_phyerrs; } ;
struct wmi_phyerr_hdr_arg {void const* phyerrs; void* buf_len; void* tsf_u32; void* tsf_l32; void* num_phyerrs; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 size_t WMI_TLV_TAG_ARRAY_BYTE ; 
 size_t WMI_TLV_TAG_STRUCT_COMB_PHYERR_RX_HDR ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_phyerr_ev_hdr(struct ath10k *ar,
						struct sk_buff *skb,
						struct wmi_phyerr_hdr_arg *arg)
{
	const void **tb;
	const struct wmi_tlv_phyerr_ev *ev;
	const void *phyerrs;
	int ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_COMB_PHYERR_RX_HDR];
	phyerrs = tb[WMI_TLV_TAG_ARRAY_BYTE];

	if (!ev || !phyerrs) {
		kfree(tb);
		return -EPROTO;
	}

	arg->num_phyerrs  = __le32_to_cpu(ev->num_phyerrs);
	arg->tsf_l32 = __le32_to_cpu(ev->tsf_l32);
	arg->tsf_u32 = __le32_to_cpu(ev->tsf_u32);
	arg->buf_len = __le32_to_cpu(ev->buf_len);
	arg->phyerrs = phyerrs;

	kfree(tb);
	return 0;
}