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
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct audit_buffer {struct sk_buff* skb; } ;

/* Variables and functions */
 scalar_t__ NLMSG_HDRLEN ; 
 int /*<<< orphan*/  audit_buffer_free (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 int /*<<< orphan*/  audit_queue ; 
 scalar_t__ audit_rate_check () ; 
 int /*<<< orphan*/  kauditd_wait ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void audit_log_end(struct audit_buffer *ab)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh;

	if (!ab)
		return;

	if (audit_rate_check()) {
		skb = ab->skb;
		ab->skb = NULL;

		/* setup the netlink header, see the comments in
		 * kauditd_send_multicast_skb() for length quirks */
		nlh = nlmsg_hdr(skb);
		nlh->nlmsg_len = skb->len - NLMSG_HDRLEN;

		/* queue the netlink packet and poke the kauditd thread */
		skb_queue_tail(&audit_queue, skb);
		wake_up_interruptible(&kauditd_wait);
	} else
		audit_log_lost("rate limit exceeded");

	audit_buffer_free(ab);
}