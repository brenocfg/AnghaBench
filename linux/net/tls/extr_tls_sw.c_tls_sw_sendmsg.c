#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_8__ {int err; int /*<<< orphan*/  completion; } ;
struct tls_sw_context_tx {int async_capable; TYPE_1__ tx_work; int /*<<< orphan*/  tx_bitmask; TYPE_4__ async_wait; int /*<<< orphan*/  async_notify; int /*<<< orphan*/  encrypt_pending; struct tls_rec* open_rec; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  end; } ;
struct sk_msg {TYPE_2__ sg; } ;
struct tls_rec {scalar_t__ inplace_crypto; struct sk_msg msg_encrypted; struct sk_msg msg_plaintext; } ;
struct tls_prot_info {size_t overhead_size; } ;
struct tls_context {int pending_open_record_frags; int /*<<< orphan*/  tx_lock; struct tls_prot_info prot_info; } ;
struct sock {int sk_err; TYPE_3__* sk_socket; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_controllen; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_TX_SCHEDULED ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TLS_MAX_PAYLOAD_SIZE ; 
 unsigned char TLS_RECORD_TYPE_DATA ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int bpf_exec_tx_verdict (struct sk_msg*,struct sock*,int,unsigned char,size_t*,int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_wait_req (int,TYPE_4__*) ; 
 int iov_iter_is_kvec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_revert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 size_t msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sk_msg_memcopy_from_iter (struct sock*,int /*<<< orphan*/ *,struct sk_msg*,size_t) ; 
 int /*<<< orphan*/  sk_msg_sg_copy_clear (struct sk_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_msg_sg_copy_set (struct sk_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_msg_trim (struct sock*,struct sk_msg*,int) ; 
 int sk_msg_zerocopy_from_iter (struct sock*,int /*<<< orphan*/ *,struct sk_msg*,size_t) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tls_alloc_encrypted_msg (struct sock*,int) ; 
 int tls_clone_plaintext_msg (struct sock*,int) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_rec* tls_get_rec (struct sock*) ; 
 int tls_proccess_cmsg (struct sock*,struct msghdr*,unsigned char*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_trim_both_msgs (struct sock*,int) ; 
 int /*<<< orphan*/  tls_tx_records (struct sock*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int tls_sw_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	long timeo = sock_sndtimeo(sk, msg->msg_flags & MSG_DONTWAIT);
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	bool async_capable = ctx->async_capable;
	unsigned char record_type = TLS_RECORD_TYPE_DATA;
	bool is_kvec = iov_iter_is_kvec(&msg->msg_iter);
	bool eor = !(msg->msg_flags & MSG_MORE);
	size_t try_to_copy, copied = 0;
	struct sk_msg *msg_pl, *msg_en;
	struct tls_rec *rec;
	int required_size;
	int num_async = 0;
	bool full_record;
	int record_room;
	int num_zc = 0;
	int orig_size;
	int ret = 0;

	if (msg->msg_flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL))
		return -ENOTSUPP;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);

	if (unlikely(msg->msg_controllen)) {
		ret = tls_proccess_cmsg(sk, msg, &record_type);
		if (ret) {
			if (ret == -EINPROGRESS)
				num_async++;
			else if (ret != -EAGAIN)
				goto send_end;
		}
	}

	while (msg_data_left(msg)) {
		if (sk->sk_err) {
			ret = -sk->sk_err;
			goto send_end;
		}

		if (ctx->open_rec)
			rec = ctx->open_rec;
		else
			rec = ctx->open_rec = tls_get_rec(sk);
		if (!rec) {
			ret = -ENOMEM;
			goto send_end;
		}

		msg_pl = &rec->msg_plaintext;
		msg_en = &rec->msg_encrypted;

		orig_size = msg_pl->sg.size;
		full_record = false;
		try_to_copy = msg_data_left(msg);
		record_room = TLS_MAX_PAYLOAD_SIZE - msg_pl->sg.size;
		if (try_to_copy >= record_room) {
			try_to_copy = record_room;
			full_record = true;
		}

		required_size = msg_pl->sg.size + try_to_copy +
				prot->overhead_size;

		if (!sk_stream_memory_free(sk))
			goto wait_for_sndbuf;

alloc_encrypted:
		ret = tls_alloc_encrypted_msg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto wait_for_memory;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - msg_en->sg.size;
			full_record = true;
		}

		if (!is_kvec && (full_record || eor) && !async_capable) {
			u32 first = msg_pl->sg.end;

			ret = sk_msg_zerocopy_from_iter(sk, &msg->msg_iter,
							msg_pl, try_to_copy);
			if (ret)
				goto fallback_to_reg_send;

			rec->inplace_crypto = 0;

			num_zc++;
			copied += try_to_copy;

			sk_msg_sg_copy_set(msg_pl, first);
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied,
						  msg->msg_flags);
			if (ret) {
				if (ret == -EINPROGRESS)
					num_async++;
				else if (ret == -ENOMEM)
					goto wait_for_memory;
				else if (ret == -ENOSPC)
					goto rollback_iter;
				else if (ret != -EAGAIN)
					goto send_end;
			}
			continue;
rollback_iter:
			copied -= try_to_copy;
			sk_msg_sg_copy_clear(msg_pl, first);
			iov_iter_revert(&msg->msg_iter,
					msg_pl->sg.size - orig_size);
fallback_to_reg_send:
			sk_msg_trim(sk, msg_pl, orig_size);
		}

		required_size = msg_pl->sg.size + try_to_copy;

		ret = tls_clone_plaintext_msg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto send_end;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - msg_pl->sg.size;
			full_record = true;
			sk_msg_trim(sk, msg_en,
				    msg_pl->sg.size + prot->overhead_size);
		}

		if (try_to_copy) {
			ret = sk_msg_memcopy_from_iter(sk, &msg->msg_iter,
						       msg_pl, try_to_copy);
			if (ret < 0)
				goto trim_sgl;
		}

		/* Open records defined only if successfully copied, otherwise
		 * we would trim the sg but not reset the open record frags.
		 */
		tls_ctx->pending_open_record_frags = true;
		copied += try_to_copy;
		if (full_record || eor) {
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied,
						  msg->msg_flags);
			if (ret) {
				if (ret == -EINPROGRESS)
					num_async++;
				else if (ret == -ENOMEM)
					goto wait_for_memory;
				else if (ret != -EAGAIN) {
					if (ret == -ENOSPC)
						ret = 0;
					goto send_end;
				}
			}
		}

		continue;

wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		ret = sk_stream_wait_memory(sk, &timeo);
		if (ret) {
trim_sgl:
			tls_trim_both_msgs(sk, orig_size);
			goto send_end;
		}

		if (msg_en->sg.size < required_size)
			goto alloc_encrypted;
	}

	if (!num_async) {
		goto send_end;
	} else if (num_zc) {
		/* Wait for pending encryptions to get completed */
		smp_store_mb(ctx->async_notify, true);

		if (atomic_read(&ctx->encrypt_pending))
			crypto_wait_req(-EINPROGRESS, &ctx->async_wait);
		else
			reinit_completion(&ctx->async_wait.completion);

		WRITE_ONCE(ctx->async_notify, false);

		if (ctx->async_wait.err) {
			ret = ctx->async_wait.err;
			copied = 0;
		}
	}

	/* Transmit if any encryptions have completed */
	if (test_and_clear_bit(BIT_TX_SCHEDULED, &ctx->tx_bitmask)) {
		cancel_delayed_work(&ctx->tx_work.work);
		tls_tx_records(sk, msg->msg_flags);
	}

send_end:
	ret = sk_stream_error(sk, msg->msg_flags, ret);

	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	return copied ? copied : ret;
}