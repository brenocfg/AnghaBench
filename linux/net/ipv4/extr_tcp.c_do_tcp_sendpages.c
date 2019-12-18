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
struct tcp_sock {int /*<<< orphan*/  nonagle; scalar_t__ write_seq; } ;
struct sock {int sk_state; int sk_shutdown; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_tsflags; TYPE_1__* sk_socket; int /*<<< orphan*/  sk_allocation; scalar_t__ sk_err; } ;
struct sk_buff {int len; int decrypted; int data_len; int truesize; int /*<<< orphan*/  ip_summed; } ;
struct page {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int end_seq; int /*<<< orphan*/  tcp_flags; } ;
struct TYPE_5__ {int nr_frags; int /*<<< orphan*/  tx_flags; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CONFIG_DEBUG_VM ; 
 int EAGAIN ; 
 scalar_t__ EINVAL ; 
 int EPIPE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NO_SHARED_FRAGS ; 
 int MSG_OOB ; 
 int MSG_SENDPAGE_DECRYPTED ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SKBTX_SHARED_FRAG ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TCPF_CLOSE_WAIT ; 
 int TCPF_ESTABLISHED ; 
 int /*<<< orphan*/  TCPHDR_PSH ; 
 int /*<<< orphan*/  TCP_CHRONO_SNDBUF_LIMITED ; 
 int /*<<< orphan*/  TCP_NAGLE_PUSH ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __tcp_push_pending_frames (struct sock*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ forced_push (struct tcp_sock*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int) ; 
 struct sk_buff* sk_stream_alloc_skb (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_connect (struct sock*,long*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 int /*<<< orphan*/  sk_wmem_queued_add (struct sock*,int) ; 
 int /*<<< orphan*/  sk_wmem_schedule (struct sock*,int) ; 
 int skb_can_coalesce (struct sk_buff*,int,struct page*,int) ; 
 int /*<<< orphan*/  skb_entail (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int,int) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int sysctl_max_skb_frags ; 
 int /*<<< orphan*/  tcp_chrono_stop (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_mark_push (struct tcp_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_passive_fastopen (struct sock*) ; 
 int /*<<< orphan*/  tcp_push (struct sock*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_push_one (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_remove_empty_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_rtx_and_write_queues_empty (struct sock*) ; 
 struct sk_buff* tcp_send_head (struct sock*) ; 
 int tcp_send_mss (struct sock*,int*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_skb_can_collapse_to (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_skb_pcount_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_tx_timestamp (struct sock*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_write_queue_tail (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

ssize_t do_tcp_sendpages(struct sock *sk, struct page *page, int offset,
			 size_t size, int flags)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int mss_now, size_goal;
	int err;
	ssize_t copied;
	long timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);

	if (IS_ENABLED(CONFIG_DEBUG_VM) &&
	    WARN_ONCE(PageSlab(page), "page must not be a Slab one"))
		return -EINVAL;

	/* Wait for a connection to finish. One exception is TCP Fast Open
	 * (passive side) where data is allowed to be sent before a connection
	 * is fully established.
	 */
	if (((1 << sk->sk_state) & ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) &&
	    !tcp_passive_fastopen(sk)) {
		err = sk_stream_wait_connect(sk, &timeo);
		if (err != 0)
			goto out_err;
	}

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	mss_now = tcp_send_mss(sk, &size_goal, flags);
	copied = 0;

	err = -EPIPE;
	if (sk->sk_err || (sk->sk_shutdown & SEND_SHUTDOWN))
		goto out_err;

	while (size > 0) {
		struct sk_buff *skb = tcp_write_queue_tail(sk);
		int copy, i;
		bool can_coalesce;

		if (!skb || (copy = size_goal - skb->len) <= 0 ||
		    !tcp_skb_can_collapse_to(skb)) {
new_segment:
			if (!sk_stream_memory_free(sk))
				goto wait_for_sndbuf;

			skb = sk_stream_alloc_skb(sk, 0, sk->sk_allocation,
					tcp_rtx_and_write_queues_empty(sk));
			if (!skb)
				goto wait_for_memory;

#ifdef CONFIG_TLS_DEVICE
			skb->decrypted = !!(flags & MSG_SENDPAGE_DECRYPTED);
#endif
			skb_entail(sk, skb);
			copy = size_goal;
		}

		if (copy > size)
			copy = size;

		i = skb_shinfo(skb)->nr_frags;
		can_coalesce = skb_can_coalesce(skb, i, page, offset);
		if (!can_coalesce && i >= sysctl_max_skb_frags) {
			tcp_mark_push(tp, skb);
			goto new_segment;
		}
		if (!sk_wmem_schedule(sk, copy))
			goto wait_for_memory;

		if (can_coalesce) {
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
		} else {
			get_page(page);
			skb_fill_page_desc(skb, i, page, offset, copy);
		}

		if (!(flags & MSG_NO_SHARED_FRAGS))
			skb_shinfo(skb)->tx_flags |= SKBTX_SHARED_FRAG;

		skb->len += copy;
		skb->data_len += copy;
		skb->truesize += copy;
		sk_wmem_queued_add(sk, copy);
		sk_mem_charge(sk, copy);
		skb->ip_summed = CHECKSUM_PARTIAL;
		WRITE_ONCE(tp->write_seq, tp->write_seq + copy);
		TCP_SKB_CB(skb)->end_seq += copy;
		tcp_skb_pcount_set(skb, 0);

		if (!copied)
			TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_PSH;

		copied += copy;
		offset += copy;
		size -= copy;
		if (!size)
			goto out;

		if (skb->len < size_goal || (flags & MSG_OOB))
			continue;

		if (forced_push(tp)) {
			tcp_mark_push(tp, skb);
			__tcp_push_pending_frames(sk, mss_now, TCP_NAGLE_PUSH);
		} else if (skb == tcp_send_head(sk))
			tcp_push_one(sk, mss_now);
		continue;

wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		tcp_push(sk, flags & ~MSG_MORE, mss_now,
			 TCP_NAGLE_PUSH, size_goal);

		err = sk_stream_wait_memory(sk, &timeo);
		if (err != 0)
			goto do_error;

		mss_now = tcp_send_mss(sk, &size_goal, flags);
	}

out:
	if (copied) {
		tcp_tx_timestamp(sk, sk->sk_tsflags);
		if (!(flags & MSG_SENDPAGE_NOTLAST))
			tcp_push(sk, flags, mss_now, tp->nonagle, size_goal);
	}
	return copied;

do_error:
	tcp_remove_empty_skb(sk, tcp_write_queue_tail(sk));
	if (copied)
		goto out;
out_err:
	/* make sure we wake any epoll edge trigger waiter */
	if (unlikely(skb_queue_len(&sk->sk_write_queue) == 0 &&
		     err == -EAGAIN)) {
		sk->sk_write_space(sk);
		tcp_chrono_stop(sk, TCP_CHRONO_SNDBUF_LIMITED);
	}
	return sk_stream_error(sk, flags, err);
}