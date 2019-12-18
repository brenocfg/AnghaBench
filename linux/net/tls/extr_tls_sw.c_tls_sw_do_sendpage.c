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
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct tls_sw_context_tx {TYPE_3__ tx_work; int /*<<< orphan*/  tx_bitmask; struct tls_rec* open_rec; } ;
struct TYPE_5__ {size_t size; } ;
struct sk_msg {TYPE_2__ sg; } ;
struct tls_rec {scalar_t__ inplace_crypto; struct sk_msg msg_plaintext; } ;
struct tls_prot_info {size_t overhead_size; } ;
struct tls_context {int pending_open_record_frags; struct tls_prot_info prot_info; } ;
struct sock {int sk_err; TYPE_1__* sk_socket; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_TX_SCHEDULED ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TLS_MAX_PAYLOAD_SIZE ; 
 unsigned char TLS_RECORD_TYPE_DATA ; 
 int bpf_exec_tx_verdict (struct sk_msg*,struct sock*,int,unsigned char,size_t*,int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,size_t) ; 
 scalar_t__ sk_msg_full (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_page_add (struct sk_msg*,struct page*,size_t,int) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tls_alloc_encrypted_msg (struct sock*,size_t) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_rec* tls_get_rec (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_trim_both_msgs (struct sock*,size_t) ; 
 int /*<<< orphan*/  tls_tx_records (struct sock*,int) ; 

__attribute__((used)) static int tls_sw_do_sendpage(struct sock *sk, struct page *page,
			      int offset, size_t size, int flags)
{
	long timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	unsigned char record_type = TLS_RECORD_TYPE_DATA;
	struct sk_msg *msg_pl;
	struct tls_rec *rec;
	int num_async = 0;
	size_t copied = 0;
	bool full_record;
	int record_room;
	int ret = 0;
	bool eor;

	eor = !(flags & (MSG_MORE | MSG_SENDPAGE_NOTLAST));
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	/* Call the sk_stream functions to manage the sndbuf mem. */
	while (size > 0) {
		size_t copy, required_size;

		if (sk->sk_err) {
			ret = -sk->sk_err;
			goto sendpage_end;
		}

		if (ctx->open_rec)
			rec = ctx->open_rec;
		else
			rec = ctx->open_rec = tls_get_rec(sk);
		if (!rec) {
			ret = -ENOMEM;
			goto sendpage_end;
		}

		msg_pl = &rec->msg_plaintext;

		full_record = false;
		record_room = TLS_MAX_PAYLOAD_SIZE - msg_pl->sg.size;
		copy = size;
		if (copy >= record_room) {
			copy = record_room;
			full_record = true;
		}

		required_size = msg_pl->sg.size + copy + prot->overhead_size;

		if (!sk_stream_memory_free(sk))
			goto wait_for_sndbuf;
alloc_payload:
		ret = tls_alloc_encrypted_msg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto wait_for_memory;

			/* Adjust copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			copy -= required_size - msg_pl->sg.size;
			full_record = true;
		}

		sk_msg_page_add(msg_pl, page, copy, offset);
		sk_mem_charge(sk, copy);

		offset += copy;
		size -= copy;
		copied += copy;

		tls_ctx->pending_open_record_frags = true;
		if (full_record || eor || sk_msg_full(msg_pl)) {
			rec->inplace_crypto = 0;
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied, flags);
			if (ret) {
				if (ret == -EINPROGRESS)
					num_async++;
				else if (ret == -ENOMEM)
					goto wait_for_memory;
				else if (ret != -EAGAIN) {
					if (ret == -ENOSPC)
						ret = 0;
					goto sendpage_end;
				}
			}
		}
		continue;
wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		ret = sk_stream_wait_memory(sk, &timeo);
		if (ret) {
			tls_trim_both_msgs(sk, msg_pl->sg.size);
			goto sendpage_end;
		}

		goto alloc_payload;
	}

	if (num_async) {
		/* Transmit if any encryptions have completed */
		if (test_and_clear_bit(BIT_TX_SCHEDULED, &ctx->tx_bitmask)) {
			cancel_delayed_work(&ctx->tx_work.work);
			tls_tx_records(sk, flags);
		}
	}
sendpage_end:
	ret = sk_stream_error(sk, flags, ret);
	return copied ? copied : ret;
}