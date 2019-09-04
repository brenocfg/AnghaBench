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
struct wmi_roam_ev_arg {int /*<<< orphan*/  reason; int /*<<< orphan*/  vdev_id; } ;
struct wmi_roam_ev {int /*<<< orphan*/  reason; int /*<<< orphan*/  vdev_id; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int ath10k_wmi_op_pull_roam_ev(struct ath10k *ar, struct sk_buff *skb,
				      struct wmi_roam_ev_arg *arg)
{
	struct wmi_roam_ev *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	skb_pull(skb, sizeof(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->reason = ev->reason;

	return 0;
}