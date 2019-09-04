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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int data; int len; } ;
struct ath10k_htc_hdr {int trailer_len; int flags; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ep_rx_complete ) (struct ath10k*,struct sk_buff*) ;} ;
struct ath10k_htc_ep {scalar_t__ service_id; TYPE_1__ ep_ops; } ;
struct ath10k_htc {struct ath10k_htc_ep* endpoint; } ;
struct ath10k {struct ath10k_htc htc; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int ATH10K_HTC_FLAG_TRAILER_PRESENT ; 
 int ath10k_htc_process_trailer (struct ath10k_htc*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int eid_from_htc_hdr (struct ath10k_htc_hdr*) ; 
 scalar_t__ is_trailer_only_msg (struct ath10k_htc_hdr*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_usb_rx_complete(struct ath10k *ar, struct sk_buff *skb)
{
	struct ath10k_htc *htc = &ar->htc;
	struct ath10k_htc_hdr *htc_hdr;
	enum ath10k_htc_ep_id eid;
	struct ath10k_htc_ep *ep;
	u16 payload_len;
	u8 *trailer;
	int ret;

	htc_hdr = (struct ath10k_htc_hdr *)skb->data;
	eid = eid_from_htc_hdr(htc_hdr);
	ep = &ar->htc.endpoint[eid];

	if (ep->service_id == 0) {
		ath10k_warn(ar, "ep %d is not connected\n", eid);
		goto out_free_skb;
	}

	payload_len = le16_to_cpu(htc_hdr->len);
	if (!payload_len) {
		ath10k_warn(ar, "zero length frame received, firmware crashed?\n");
		goto out_free_skb;
	}

	if (payload_len < htc_hdr->trailer_len) {
		ath10k_warn(ar, "malformed frame received, firmware crashed?\n");
		goto out_free_skb;
	}

	if (htc_hdr->flags & ATH10K_HTC_FLAG_TRAILER_PRESENT) {
		trailer = skb->data + sizeof(*htc_hdr) + payload_len -
			  htc_hdr->trailer_len;

		ret = ath10k_htc_process_trailer(htc,
						 trailer,
						 htc_hdr->trailer_len,
						 eid,
						 NULL,
						 NULL);
		if (ret)
			goto out_free_skb;

		if (is_trailer_only_msg(htc_hdr))
			goto out_free_skb;

		/* strip off the trailer from the skb since it should not
		 * be passed on to upper layers
		 */
		skb_trim(skb, skb->len - htc_hdr->trailer_len);
	}

	skb_pull(skb, sizeof(*htc_hdr));
	ep->ep_ops.ep_rx_complete(ar, skb);
	/* The RX complete handler now owns the skb... */

	return;

out_free_skb:
	dev_kfree_skb(skb);
}