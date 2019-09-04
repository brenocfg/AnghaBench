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
struct wmi_chan_info_event {int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  rx_clear_count; int /*<<< orphan*/  noise_floor; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  freq; int /*<<< orphan*/  err_code; } ;
struct wmi_ch_info_ev_arg {int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  rx_clear_count; int /*<<< orphan*/  noise_floor; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  freq; int /*<<< orphan*/  err_code; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int ath10k_wmi_op_pull_ch_info_ev(struct ath10k *ar, struct sk_buff *skb,
					 struct wmi_ch_info_ev_arg *arg)
{
	struct wmi_chan_info_event *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	skb_pull(skb, sizeof(*ev));
	arg->err_code = ev->err_code;
	arg->freq = ev->freq;
	arg->cmd_flags = ev->cmd_flags;
	arg->noise_floor = ev->noise_floor;
	arg->rx_clear_count = ev->rx_clear_count;
	arg->cycle_count = ev->cycle_count;

	return 0;
}