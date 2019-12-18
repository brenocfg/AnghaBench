#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {unsigned int sk_wmem_queued; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {struct sk_buff* next; } ;
struct kcm_tx_msg {int sent; unsigned short frag_offset; unsigned short fragidx; struct sk_buff* frag_skb; } ;
struct kcm_sock {int tx_wait_more; struct kcm_psock* tx_psock; struct sock sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_msgs; int /*<<< orphan*/  tx_bytes; } ;
struct kcm_psock {TYPE_2__ stats; TYPE_1__* sk; scalar_t__ tx_stopped; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_6__ {unsigned short nr_frags; struct sk_buff* frag_list; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_socket; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  KCM_STATS_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kcm_abort_tx_psock (struct kcm_psock*,int,int) ; 
 int /*<<< orphan*/  kcm_report_tx_retry (struct kcm_sock*) ; 
 struct kcm_tx_msg* kcm_tx_msg (struct sk_buff*) ; 
 int kernel_sendpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct kcm_psock* reserve_psock (struct kcm_sock*) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned short skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unreserve_psock (struct kcm_sock*) ; 

__attribute__((used)) static int kcm_write_msgs(struct kcm_sock *kcm)
{
	struct sock *sk = &kcm->sk;
	struct kcm_psock *psock;
	struct sk_buff *skb, *head;
	struct kcm_tx_msg *txm;
	unsigned short fragidx, frag_offset;
	unsigned int sent, total_sent = 0;
	int ret = 0;

	kcm->tx_wait_more = false;
	psock = kcm->tx_psock;
	if (unlikely(psock && psock->tx_stopped)) {
		/* A reserved psock was aborted asynchronously. Unreserve
		 * it and we'll retry the message.
		 */
		unreserve_psock(kcm);
		kcm_report_tx_retry(kcm);
		if (skb_queue_empty(&sk->sk_write_queue))
			return 0;

		kcm_tx_msg(skb_peek(&sk->sk_write_queue))->sent = 0;

	} else if (skb_queue_empty(&sk->sk_write_queue)) {
		return 0;
	}

	head = skb_peek(&sk->sk_write_queue);
	txm = kcm_tx_msg(head);

	if (txm->sent) {
		/* Send of first skbuff in queue already in progress */
		if (WARN_ON(!psock)) {
			ret = -EINVAL;
			goto out;
		}
		sent = txm->sent;
		frag_offset = txm->frag_offset;
		fragidx = txm->fragidx;
		skb = txm->frag_skb;

		goto do_frag;
	}

try_again:
	psock = reserve_psock(kcm);
	if (!psock)
		goto out;

	do {
		skb = head;
		txm = kcm_tx_msg(head);
		sent = 0;

do_frag_list:
		if (WARN_ON(!skb_shinfo(skb)->nr_frags)) {
			ret = -EINVAL;
			goto out;
		}

		for (fragidx = 0; fragidx < skb_shinfo(skb)->nr_frags;
		     fragidx++) {
			skb_frag_t *frag;

			frag_offset = 0;
do_frag:
			frag = &skb_shinfo(skb)->frags[fragidx];
			if (WARN_ON(!skb_frag_size(frag))) {
				ret = -EINVAL;
				goto out;
			}

			ret = kernel_sendpage(psock->sk->sk_socket,
					      skb_frag_page(frag),
					      skb_frag_off(frag) + frag_offset,
					      skb_frag_size(frag) - frag_offset,
					      MSG_DONTWAIT);
			if (ret <= 0) {
				if (ret == -EAGAIN) {
					/* Save state to try again when there's
					 * write space on the socket
					 */
					txm->sent = sent;
					txm->frag_offset = frag_offset;
					txm->fragidx = fragidx;
					txm->frag_skb = skb;

					ret = 0;
					goto out;
				}

				/* Hard failure in sending message, abort this
				 * psock since it has lost framing
				 * synchonization and retry sending the
				 * message from the beginning.
				 */
				kcm_abort_tx_psock(psock, ret ? -ret : EPIPE,
						   true);
				unreserve_psock(kcm);

				txm->sent = 0;
				kcm_report_tx_retry(kcm);
				ret = 0;

				goto try_again;
			}

			sent += ret;
			frag_offset += ret;
			KCM_STATS_ADD(psock->stats.tx_bytes, ret);
			if (frag_offset < skb_frag_size(frag)) {
				/* Not finished with this frag */
				goto do_frag;
			}
		}

		if (skb == head) {
			if (skb_has_frag_list(skb)) {
				skb = skb_shinfo(skb)->frag_list;
				goto do_frag_list;
			}
		} else if (skb->next) {
			skb = skb->next;
			goto do_frag_list;
		}

		/* Successfully sent the whole packet, account for it. */
		skb_dequeue(&sk->sk_write_queue);
		kfree_skb(head);
		sk->sk_wmem_queued -= sent;
		total_sent += sent;
		KCM_STATS_INCR(psock->stats.tx_msgs);
	} while ((head = skb_peek(&sk->sk_write_queue)));
out:
	if (!head) {
		/* Done with all queued messages. */
		WARN_ON(!skb_queue_empty(&sk->sk_write_queue));
		unreserve_psock(kcm);
	}

	/* Check if write space is available */
	sk->sk_write_space(sk);

	return total_sent ? : ret;
}