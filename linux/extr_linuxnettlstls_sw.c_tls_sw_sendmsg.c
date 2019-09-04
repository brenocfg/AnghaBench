#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tls_sw_context_tx {int sg_plaintext_size; int sg_encrypted_size; int /*<<< orphan*/  sg_encrypted_num_elem; int /*<<< orphan*/  sg_encrypted_data; int /*<<< orphan*/  sg_plaintext_num_elem; int /*<<< orphan*/  sg_plaintext_data; } ;
struct TYPE_5__ {size_t overhead_size; } ;
struct tls_context {TYPE_1__ tx; } ;
struct sock {int sk_err; TYPE_2__* sk_socket; } ;
struct TYPE_7__ {int type; } ;
struct msghdr {int msg_flags; TYPE_3__ msg_iter; int /*<<< orphan*/  msg_controllen; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOTSUPP ; 
 int ITER_KVEC ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TLS_MAX_PAYLOAD_SIZE ; 
 unsigned char TLS_RECORD_TYPE_DATA ; 
 int alloc_encrypted_sg (struct sock*,int) ; 
 int alloc_plaintext_sg (struct sock*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcopy_from_iter (struct sock*,TYPE_3__*,size_t) ; 
 size_t msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 scalar_t__ tls_complete_pending_work (struct sock*,struct tls_context*,int,long*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 scalar_t__ tls_is_pending_closed_record (struct tls_context*) ; 
 int tls_proccess_cmsg (struct sock*,struct msghdr*,unsigned char*) ; 
 int tls_push_record (struct sock*,int,unsigned char) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  trim_both_sgl (struct sock*,int) ; 
 int /*<<< orphan*/  trim_sg (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int zerocopy_from_iter (struct sock*,TYPE_3__*,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int tls_sw_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	int ret = 0;
	int required_size;
	long timeo = sock_sndtimeo(sk, msg->msg_flags & MSG_DONTWAIT);
	bool eor = !(msg->msg_flags & MSG_MORE);
	size_t try_to_copy, copied = 0;
	unsigned char record_type = TLS_RECORD_TYPE_DATA;
	int record_room;
	bool full_record;
	int orig_size;
	bool is_kvec = msg->msg_iter.type & ITER_KVEC;

	if (msg->msg_flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL))
		return -ENOTSUPP;

	lock_sock(sk);

	if (tls_complete_pending_work(sk, tls_ctx, msg->msg_flags, &timeo))
		goto send_end;

	if (unlikely(msg->msg_controllen)) {
		ret = tls_proccess_cmsg(sk, msg, &record_type);
		if (ret)
			goto send_end;
	}

	while (msg_data_left(msg)) {
		if (sk->sk_err) {
			ret = -sk->sk_err;
			goto send_end;
		}

		orig_size = ctx->sg_plaintext_size;
		full_record = false;
		try_to_copy = msg_data_left(msg);
		record_room = TLS_MAX_PAYLOAD_SIZE - ctx->sg_plaintext_size;
		if (try_to_copy >= record_room) {
			try_to_copy = record_room;
			full_record = true;
		}

		required_size = ctx->sg_plaintext_size + try_to_copy +
				tls_ctx->tx.overhead_size;

		if (!sk_stream_memory_free(sk))
			goto wait_for_sndbuf;
alloc_encrypted:
		ret = alloc_encrypted_sg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto wait_for_memory;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - ctx->sg_encrypted_size;
			full_record = true;
		}
		if (!is_kvec && (full_record || eor)) {
			ret = zerocopy_from_iter(sk, &msg->msg_iter,
				try_to_copy, &ctx->sg_plaintext_num_elem,
				&ctx->sg_plaintext_size,
				ctx->sg_plaintext_data,
				ARRAY_SIZE(ctx->sg_plaintext_data),
				true);
			if (ret)
				goto fallback_to_reg_send;

			copied += try_to_copy;
			ret = tls_push_record(sk, msg->msg_flags, record_type);
			if (ret)
				goto send_end;
			continue;

fallback_to_reg_send:
			trim_sg(sk, ctx->sg_plaintext_data,
				&ctx->sg_plaintext_num_elem,
				&ctx->sg_plaintext_size,
				orig_size);
		}

		required_size = ctx->sg_plaintext_size + try_to_copy;
alloc_plaintext:
		ret = alloc_plaintext_sg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto wait_for_memory;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - ctx->sg_plaintext_size;
			full_record = true;

			trim_sg(sk, ctx->sg_encrypted_data,
				&ctx->sg_encrypted_num_elem,
				&ctx->sg_encrypted_size,
				ctx->sg_plaintext_size +
				tls_ctx->tx.overhead_size);
		}

		ret = memcopy_from_iter(sk, &msg->msg_iter, try_to_copy);
		if (ret)
			goto trim_sgl;

		copied += try_to_copy;
		if (full_record || eor) {
push_record:
			ret = tls_push_record(sk, msg->msg_flags, record_type);
			if (ret) {
				if (ret == -ENOMEM)
					goto wait_for_memory;

				goto send_end;
			}
		}

		continue;

wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		ret = sk_stream_wait_memory(sk, &timeo);
		if (ret) {
trim_sgl:
			trim_both_sgl(sk, orig_size);
			goto send_end;
		}

		if (tls_is_pending_closed_record(tls_ctx))
			goto push_record;

		if (ctx->sg_encrypted_size < required_size)
			goto alloc_encrypted;

		goto alloc_plaintext;
	}

send_end:
	ret = sk_stream_error(sk, msg->msg_flags, ret);

	release_sock(sk);
	return copied ? copied : ret;
}