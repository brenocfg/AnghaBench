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
struct sock {int sk_state; } ;
struct sk_buff {int dummy; } ;
struct pep_sock {int /*<<< orphan*/  tx_credits; scalar_t__ aligned; } ;
struct msghdr {int msg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ECONNRESET ; 
 int EMSGSIZE ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ MAX_PHONET_HEADER ; 
 scalar_t__ MAX_PNPIPE_HEADER ; 
 int MSG_CMSG_COMPAT ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_NOSIGNAL ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int TCP_CLOSE_WAIT ; 
 int TCP_ESTABLISHED ; 
 size_t USHRT_MAX ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pipe_skb_send (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sk_stream_wait_connect (struct sock*,long*) ; 
 int sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,scalar_t__,int,int*) ; 
 int sock_intr_errno (long) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int pep_sendmsg(struct sock *sk, struct msghdr *msg, size_t len)
{
	struct pep_sock *pn = pep_sk(sk);
	struct sk_buff *skb;
	long timeo;
	int flags = msg->msg_flags;
	int err, done;

	if (len > USHRT_MAX)
		return -EMSGSIZE;

	if ((msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|
				MSG_CMSG_COMPAT)) ||
			!(msg->msg_flags & MSG_EOR))
		return -EOPNOTSUPP;

	skb = sock_alloc_send_skb(sk, MAX_PNPIPE_HEADER + len,
					flags & MSG_DONTWAIT, &err);
	if (!skb)
		return err;

	skb_reserve(skb, MAX_PHONET_HEADER + 3 + pn->aligned);
	err = memcpy_from_msg(skb_put(skb, len), msg, len);
	if (err < 0)
		goto outfree;

	lock_sock(sk);
	timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	if ((1 << sk->sk_state) & (TCPF_LISTEN|TCPF_CLOSE)) {
		err = -ENOTCONN;
		goto out;
	}
	if (sk->sk_state != TCP_ESTABLISHED) {
		/* Wait until the pipe gets to enabled state */
disabled:
		err = sk_stream_wait_connect(sk, &timeo);
		if (err)
			goto out;

		if (sk->sk_state == TCP_CLOSE_WAIT) {
			err = -ECONNRESET;
			goto out;
		}
	}
	BUG_ON(sk->sk_state != TCP_ESTABLISHED);

	/* Wait until flow control allows TX */
	done = atomic_read(&pn->tx_credits);
	while (!done) {
		DEFINE_WAIT_FUNC(wait, woken_wake_function);

		if (!timeo) {
			err = -EAGAIN;
			goto out;
		}
		if (signal_pending(current)) {
			err = sock_intr_errno(timeo);
			goto out;
		}

		add_wait_queue(sk_sleep(sk), &wait);
		done = sk_wait_event(sk, &timeo, atomic_read(&pn->tx_credits), &wait);
		remove_wait_queue(sk_sleep(sk), &wait);

		if (sk->sk_state != TCP_ESTABLISHED)
			goto disabled;
	}

	err = pipe_skb_send(sk, skb);
	if (err >= 0)
		err = len; /* success! */
	skb = NULL;
out:
	release_sock(sk);
outfree:
	kfree_skb(skb);
	return err;
}