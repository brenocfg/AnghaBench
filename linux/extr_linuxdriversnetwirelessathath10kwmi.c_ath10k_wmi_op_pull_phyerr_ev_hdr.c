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
struct wmi_phyerr_hdr_arg {int buf_len; int /*<<< orphan*/  phyerrs; void* tsf_u32; void* tsf_l32; void* num_phyerrs; } ;
struct wmi_phyerr_event {int /*<<< orphan*/  phyerrs; int /*<<< orphan*/  tsf_u32; int /*<<< orphan*/  tsf_l32; int /*<<< orphan*/  num_phyerrs; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_wmi_op_pull_phyerr_ev_hdr(struct ath10k *ar,
					    struct sk_buff *skb,
					    struct wmi_phyerr_hdr_arg *arg)
{
	struct wmi_phyerr_event *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	arg->num_phyerrs = __le32_to_cpu(ev->num_phyerrs);
	arg->tsf_l32 = __le32_to_cpu(ev->tsf_l32);
	arg->tsf_u32 = __le32_to_cpu(ev->tsf_u32);
	arg->buf_len = skb->len - sizeof(*ev);
	arg->phyerrs = ev->phyerrs;

	return 0;
}