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
struct sock {int sk_err; TYPE_1__* sk_socket; } ;
struct smap_psock {int cork_bytes; int sg_size; struct sk_msg_buff* cork; int /*<<< orphan*/  eval; int /*<<< orphan*/  refcnt; } ;
struct sk_msg_buff {scalar_t__ sg_end; int /*<<< orphan*/  sg_start; struct scatterlist* sg_data; scalar_t__ sg_curr; scalar_t__ sg_copybreak; int /*<<< orphan*/  member_0; } ;
struct scatterlist {int dummy; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iter; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int MSG_DONTWAIT ; 
 int MSG_NO_SHARED_FRAGS ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  __SK_NONE ; 
 int bpf_exec_tx_verdict (struct smap_psock*,struct sk_msg_buff*,struct sock*,int*,int) ; 
 int /*<<< orphan*/  free_curr_sg (struct sock*,struct sk_msg_buff*) ; 
 int /*<<< orphan*/  free_start_sg (struct sock*,struct sk_msg_buff*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcopy_from_iter (struct sock*,struct sk_msg_buff*,int /*<<< orphan*/ *,int) ; 
 int msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_marker (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int sk_alloc_sg (struct sock*,int,struct scatterlist*,int /*<<< orphan*/ ,scalar_t__*,unsigned int*,scalar_t__) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  smap_release_sock (struct smap_psock*,struct sock*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int tcp_sendmsg (struct sock*,struct msghdr*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_tcp_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	int flags = msg->msg_flags | MSG_NO_SHARED_FRAGS;
	struct sk_msg_buff md = {0};
	unsigned int sg_copy = 0;
	struct smap_psock *psock;
	int copied = 0, err = 0;
	struct scatterlist *sg;
	long timeo;

	/* Its possible a sock event or user removed the psock _but_ the ops
	 * have not been reprogrammed yet so we get here. In this case fallback
	 * to tcp_sendmsg. Note this only works because we _only_ ever allow
	 * a single ULP there is no hierarchy here.
	 */
	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		return tcp_sendmsg(sk, msg, size);
	}

	/* Increment the psock refcnt to ensure its not released while sending a
	 * message. Required because sk lookup and bpf programs are used in
	 * separate rcu critical sections. Its OK if we lose the map entry
	 * but we can't lose the sock reference.
	 */
	if (!refcount_inc_not_zero(&psock->refcnt)) {
		rcu_read_unlock();
		return tcp_sendmsg(sk, msg, size);
	}

	sg = md.sg_data;
	sg_init_marker(sg, MAX_SKB_FRAGS);
	rcu_read_unlock();

	lock_sock(sk);
	timeo = sock_sndtimeo(sk, msg->msg_flags & MSG_DONTWAIT);

	while (msg_data_left(msg)) {
		struct sk_msg_buff *m = NULL;
		bool enospc = false;
		int copy;

		if (sk->sk_err) {
			err = -sk->sk_err;
			goto out_err;
		}

		copy = msg_data_left(msg);
		if (!sk_stream_memory_free(sk))
			goto wait_for_sndbuf;

		m = psock->cork_bytes ? psock->cork : &md;
		m->sg_curr = m->sg_copybreak ? m->sg_curr : m->sg_end;
		err = sk_alloc_sg(sk, copy, m->sg_data,
				  m->sg_start, &m->sg_end, &sg_copy,
				  m->sg_end - 1);
		if (err) {
			if (err != -ENOSPC)
				goto wait_for_memory;
			enospc = true;
			copy = sg_copy;
		}

		err = memcopy_from_iter(sk, m, &msg->msg_iter, copy);
		if (err < 0) {
			free_curr_sg(sk, m);
			goto out_err;
		}

		psock->sg_size += copy;
		copied += copy;
		sg_copy = 0;

		/* When bytes are being corked skip running BPF program and
		 * applying verdict unless there is no more buffer space. In
		 * the ENOSPC case simply run BPF prorgram with currently
		 * accumulated data. We don't have much choice at this point
		 * we could try extending the page frags or chaining complex
		 * frags but even in these cases _eventually_ we will hit an
		 * OOM scenario. More complex recovery schemes may be
		 * implemented in the future, but BPF programs must handle
		 * the case where apply_cork requests are not honored. The
		 * canonical method to verify this is to check data length.
		 */
		if (psock->cork_bytes) {
			if (copy > psock->cork_bytes)
				psock->cork_bytes = 0;
			else
				psock->cork_bytes -= copy;

			if (psock->cork_bytes && !enospc)
				goto out_cork;

			/* All cork bytes accounted for re-run filter */
			psock->eval = __SK_NONE;
			psock->cork_bytes = 0;
		}

		err = bpf_exec_tx_verdict(psock, m, sk, &copied, flags);
		if (unlikely(err < 0))
			goto out_err;
		continue;
wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		err = sk_stream_wait_memory(sk, &timeo);
		if (err) {
			if (m && m != psock->cork)
				free_start_sg(sk, m, true);
			goto out_err;
		}
	}
out_err:
	if (err < 0)
		err = sk_stream_error(sk, msg->msg_flags, err);
out_cork:
	release_sock(sk);
	smap_release_sock(psock, sk);
	return copied ? copied : err;
}