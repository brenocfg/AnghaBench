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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct tls_sw_context_tx {struct tls_rec* open_rec; } ;
struct TYPE_2__ {size_t size; } ;
struct sk_msg {size_t cork_bytes; int apply_bytes; TYPE_1__ sg; } ;
struct tls_rec {struct sk_msg msg_plaintext; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct sk_psock {int eval; struct sock* sk_redir; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOSPC ; 
 int MSG_SENDPAGE_NOPOLICY ; 
#define  __SK_DROP 130 
 int __SK_NONE ; 
#define  __SK_PASS 129 
#define  __SK_REDIRECT 128 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sk_msg*,struct sk_msg*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 size_t sk_msg_free (struct sock*,struct sk_msg*) ; 
 size_t sk_msg_free_nocharge (struct sock*,struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_free_partial (struct sock*,struct sk_msg*,int) ; 
 int sk_msg_full (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_return_zero (struct sock*,struct sk_msg*,int) ; 
 struct sk_psock* sk_psock_get (struct sock*) ; 
 int sk_psock_msg_verdict (struct sock*,struct sk_psock*,struct sk_msg*) ; 
 int /*<<< orphan*/  sk_psock_put (struct sock*,struct sk_psock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int tcp_bpf_sendmsg_redir (struct sock*,struct sk_msg*,int,int) ; 
 int /*<<< orphan*/  tls_free_open_rec (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int tls_push_record (struct sock*,int,int /*<<< orphan*/ ) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static int bpf_exec_tx_verdict(struct sk_msg *msg, struct sock *sk,
			       bool full_record, u8 record_type,
			       size_t *copied, int flags)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	struct sk_msg msg_redir = { };
	struct sk_psock *psock;
	struct sock *sk_redir;
	struct tls_rec *rec;
	bool enospc, policy;
	int err = 0, send;
	u32 delta = 0;

	policy = !(flags & MSG_SENDPAGE_NOPOLICY);
	psock = sk_psock_get(sk);
	if (!psock || !policy)
		return tls_push_record(sk, flags, record_type);
more_data:
	enospc = sk_msg_full(msg);
	if (psock->eval == __SK_NONE) {
		delta = msg->sg.size;
		psock->eval = sk_psock_msg_verdict(sk, psock, msg);
		if (delta < msg->sg.size)
			delta -= msg->sg.size;
		else
			delta = 0;
	}
	if (msg->cork_bytes && msg->cork_bytes > msg->sg.size &&
	    !enospc && !full_record) {
		err = -ENOSPC;
		goto out_err;
	}
	msg->cork_bytes = 0;
	send = msg->sg.size;
	if (msg->apply_bytes && msg->apply_bytes < send)
		send = msg->apply_bytes;

	switch (psock->eval) {
	case __SK_PASS:
		err = tls_push_record(sk, flags, record_type);
		if (err < 0) {
			*copied -= sk_msg_free(sk, msg);
			tls_free_open_rec(sk);
			goto out_err;
		}
		break;
	case __SK_REDIRECT:
		sk_redir = psock->sk_redir;
		memcpy(&msg_redir, msg, sizeof(*msg));
		if (msg->apply_bytes < send)
			msg->apply_bytes = 0;
		else
			msg->apply_bytes -= send;
		sk_msg_return_zero(sk, msg, send);
		msg->sg.size -= send;
		release_sock(sk);
		err = tcp_bpf_sendmsg_redir(sk_redir, &msg_redir, send, flags);
		lock_sock(sk);
		if (err < 0) {
			*copied -= sk_msg_free_nocharge(sk, &msg_redir);
			msg->sg.size = 0;
		}
		if (msg->sg.size == 0)
			tls_free_open_rec(sk);
		break;
	case __SK_DROP:
	default:
		sk_msg_free_partial(sk, msg, send);
		if (msg->apply_bytes < send)
			msg->apply_bytes = 0;
		else
			msg->apply_bytes -= send;
		if (msg->sg.size == 0)
			tls_free_open_rec(sk);
		*copied -= (send + delta);
		err = -EACCES;
	}

	if (likely(!err)) {
		bool reset_eval = !ctx->open_rec;

		rec = ctx->open_rec;
		if (rec) {
			msg = &rec->msg_plaintext;
			if (!msg->apply_bytes)
				reset_eval = true;
		}
		if (reset_eval) {
			psock->eval = __SK_NONE;
			if (psock->sk_redir) {
				sock_put(psock->sk_redir);
				psock->sk_redir = NULL;
			}
		}
		if (rec)
			goto more_data;
	}
 out_err:
	sk_psock_put(sk, psock);
	return err;
}