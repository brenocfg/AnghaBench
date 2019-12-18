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
struct unix_sock {int /*<<< orphan*/  iolock; int /*<<< orphan*/  peer_wait; } ;
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_type; int sk_shutdown; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct scm_cookie {int /*<<< orphan*/  fp; } ;
struct msghdr {int msg_flags; scalar_t__ msg_name; } ;
typedef  int /*<<< orphan*/  scm ;
struct TYPE_2__ {scalar_t__ fp; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int EPOLLOUT ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 int MSG_PEEK ; 
 int MSG_TRUNC ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_RCVTSTAMP ; 
 scalar_t__ SOCK_SEQPACKET ; 
 TYPE_1__ UNIXCB (struct sk_buff*) ; 
 struct sk_buff* __skb_try_recv_datagram (struct sock*,int,int /*<<< orphan*/ *,int*,int*,struct sk_buff**) ; 
 int /*<<< orphan*/  __skb_wait_for_more_packets (struct sock*,int*,long*,struct sk_buff*) ; 
 int /*<<< orphan*/  __sock_recv_timestamp (struct msghdr*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct scm_cookie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scm_fp_dup (scalar_t__) ; 
 int /*<<< orphan*/  scm_recv (struct socket*,struct msghdr*,struct scm_cookie*,int) ; 
 int /*<<< orphan*/  scm_set_cred (struct scm_cookie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_peek_offset (struct sock*,int) ; 
 int /*<<< orphan*/  sk_peek_offset_bwd (struct sock*,int) ; 
 int /*<<< orphan*/  sk_peek_offset_fwd (struct sock*,size_t) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  unix_copy_addr (struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_detach_fds (struct scm_cookie*,struct sk_buff*) ; 
 int /*<<< orphan*/  unix_set_secdata (struct scm_cookie*,struct sk_buff*) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync_poll (int /*<<< orphan*/ *,int) ; 
 scalar_t__ wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unix_dgram_recvmsg(struct socket *sock, struct msghdr *msg,
			      size_t size, int flags)
{
	struct scm_cookie scm;
	struct sock *sk = sock->sk;
	struct unix_sock *u = unix_sk(sk);
	struct sk_buff *skb, *last;
	long timeo;
	int skip;
	int err;

	err = -EOPNOTSUPP;
	if (flags&MSG_OOB)
		goto out;

	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);

	do {
		mutex_lock(&u->iolock);

		skip = sk_peek_offset(sk, flags);
		skb = __skb_try_recv_datagram(sk, flags, NULL, &skip, &err,
					      &last);
		if (skb)
			break;

		mutex_unlock(&u->iolock);

		if (err != -EAGAIN)
			break;
	} while (timeo &&
		 !__skb_wait_for_more_packets(sk, &err, &timeo, last));

	if (!skb) { /* implies iolock unlocked */
		unix_state_lock(sk);
		/* Signal EOF on disconnected non-blocking SEQPACKET socket. */
		if (sk->sk_type == SOCK_SEQPACKET && err == -EAGAIN &&
		    (sk->sk_shutdown & RCV_SHUTDOWN))
			err = 0;
		unix_state_unlock(sk);
		goto out;
	}

	if (wq_has_sleeper(&u->peer_wait))
		wake_up_interruptible_sync_poll(&u->peer_wait,
						EPOLLOUT | EPOLLWRNORM |
						EPOLLWRBAND);

	if (msg->msg_name)
		unix_copy_addr(msg, skb->sk);

	if (size > skb->len - skip)
		size = skb->len - skip;
	else if (size < skb->len - skip)
		msg->msg_flags |= MSG_TRUNC;

	err = skb_copy_datagram_msg(skb, skip, msg, size);
	if (err)
		goto out_free;

	if (sock_flag(sk, SOCK_RCVTSTAMP))
		__sock_recv_timestamp(msg, sk, skb);

	memset(&scm, 0, sizeof(scm));

	scm_set_cred(&scm, UNIXCB(skb).pid, UNIXCB(skb).uid, UNIXCB(skb).gid);
	unix_set_secdata(&scm, skb);

	if (!(flags & MSG_PEEK)) {
		if (UNIXCB(skb).fp)
			unix_detach_fds(&scm, skb);

		sk_peek_offset_bwd(sk, skb->len);
	} else {
		/* It is questionable: on PEEK we could:
		   - do not return fds - good, but too simple 8)
		   - return fds, and do not return them on read (old strategy,
		     apparently wrong)
		   - clone fds (I chose it for now, it is the most universal
		     solution)

		   POSIX 1003.1g does not actually define this clearly
		   at all. POSIX 1003.1g doesn't define a lot of things
		   clearly however!

		*/

		sk_peek_offset_fwd(sk, size);

		if (UNIXCB(skb).fp)
			scm.fp = scm_fp_dup(UNIXCB(skb).fp);
	}
	err = (flags & MSG_TRUNC) ? skb->len - skip : size;

	scm_recv(sock, msg, &scm, flags);

out_free:
	skb_free_datagram(sk, skb);
	mutex_unlock(&u->iolock);
out:
	return err;
}