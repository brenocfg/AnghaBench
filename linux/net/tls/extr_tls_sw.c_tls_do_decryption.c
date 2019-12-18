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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {struct sock* sk; } ;
struct tls_sw_context_rx {int /*<<< orphan*/  decrypt_pending; struct sk_buff async_wait; int /*<<< orphan*/  aead_recv; } ;
struct tls_prot_info {scalar_t__ tag_size; int /*<<< orphan*/  aad_size; } ;
struct tls_context {struct tls_prot_info prot_info; } ;
struct sock {int dummy; } ;
struct scatterlist {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int,struct sk_buff*) ; 
 int /*<<< orphan*/  tls_decrypt_done ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static int tls_do_decryption(struct sock *sk,
			     struct sk_buff *skb,
			     struct scatterlist *sgin,
			     struct scatterlist *sgout,
			     char *iv_recv,
			     size_t data_len,
			     struct aead_request *aead_req,
			     bool async)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	int ret;

	aead_request_set_tfm(aead_req, ctx->aead_recv);
	aead_request_set_ad(aead_req, prot->aad_size);
	aead_request_set_crypt(aead_req, sgin, sgout,
			       data_len + prot->tag_size,
			       (u8 *)iv_recv);

	if (async) {
		/* Using skb->sk to push sk through to crypto async callback
		 * handler. This allows propagating errors up to the socket
		 * if needed. It _must_ be cleared in the async handler
		 * before consume_skb is called. We _know_ skb->sk is NULL
		 * because it is a clone from strparser.
		 */
		skb->sk = sk;
		aead_request_set_callback(aead_req,
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  tls_decrypt_done, skb);
		atomic_inc(&ctx->decrypt_pending);
	} else {
		aead_request_set_callback(aead_req,
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  crypto_req_done, &ctx->async_wait);
	}

	ret = crypto_aead_decrypt(aead_req);
	if (ret == -EINPROGRESS) {
		if (async)
			return ret;

		ret = crypto_wait_req(ret, &ctx->async_wait);
	}

	if (async)
		atomic_dec(&ctx->decrypt_pending);

	return ret;
}