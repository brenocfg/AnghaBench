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
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  csum_complete_sw; int /*<<< orphan*/  csum; int /*<<< orphan*/  data; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ __skb_checksum_complete (struct sk_buff*) ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_revert (int /*<<< orphan*/ *,int) ; 
 int msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ skb_copy_and_csum_datagram (struct sk_buff*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_copy_datagram_msg (struct sk_buff*,int,struct msghdr*,int) ; 
 scalar_t__ unlikely (int) ; 

int skb_copy_and_csum_datagram_msg(struct sk_buff *skb,
				   int hlen, struct msghdr *msg)
{
	__wsum csum;
	int chunk = skb->len - hlen;

	if (!chunk)
		return 0;

	if (msg_data_left(msg) < chunk) {
		if (__skb_checksum_complete(skb))
			return -EINVAL;
		if (skb_copy_datagram_msg(skb, hlen, msg, chunk))
			goto fault;
	} else {
		csum = csum_partial(skb->data, hlen, skb->csum);
		if (skb_copy_and_csum_datagram(skb, hlen, &msg->msg_iter,
					       chunk, &csum))
			goto fault;

		if (csum_fold(csum)) {
			iov_iter_revert(&msg->msg_iter, chunk);
			return -EINVAL;
		}

		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(NULL, skb);
	}
	return 0;
fault:
	return -EFAULT;
}