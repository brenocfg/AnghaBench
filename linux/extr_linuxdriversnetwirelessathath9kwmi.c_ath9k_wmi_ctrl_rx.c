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
typedef  int u16 ;
struct wmi_cmd_hdr {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  command_id; } ;
struct wmi {scalar_t__ last_seq_id; int /*<<< orphan*/  wmi_lock; int /*<<< orphan*/  wmi_event_tasklet; int /*<<< orphan*/  wmi_event_queue; int /*<<< orphan*/  stopped; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ath9k_wmi_rsp_callback (struct wmi*,struct sk_buff*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_wmi_ctrl_rx(void *priv, struct sk_buff *skb,
			      enum htc_endpoint_id epid)
{
	struct wmi *wmi = priv;
	struct wmi_cmd_hdr *hdr;
	unsigned long flags;
	u16 cmd_id;

	if (unlikely(wmi->stopped))
		goto free_skb;

	hdr = (struct wmi_cmd_hdr *) skb->data;
	cmd_id = be16_to_cpu(hdr->command_id);

	if (cmd_id & 0x1000) {
		spin_lock_irqsave(&wmi->wmi_lock, flags);
		__skb_queue_tail(&wmi->wmi_event_queue, skb);
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);
		tasklet_schedule(&wmi->wmi_event_tasklet);
		return;
	}

	/* Check if there has been a timeout. */
	spin_lock_irqsave(&wmi->wmi_lock, flags);
	if (be16_to_cpu(hdr->seq_no) != wmi->last_seq_id) {
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);
		goto free_skb;
	}
	spin_unlock_irqrestore(&wmi->wmi_lock, flags);

	/* WMI command response */
	ath9k_wmi_rsp_callback(wmi, skb);

free_skb:
	kfree_skb(skb);
}