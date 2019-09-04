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
typedef  scalar_t__ u16 ;
struct tls_sw_context_tx {int /*<<< orphan*/  strp; int /*<<< orphan*/  sk_poll; int /*<<< orphan*/  saved_data_ready; int /*<<< orphan*/ * sg_encrypted_data; int /*<<< orphan*/ * sg_aead_out; int /*<<< orphan*/  aad_space; int /*<<< orphan*/ * sg_plaintext_data; int /*<<< orphan*/ * sg_aead_in; struct crypto_aead* aead_recv; int /*<<< orphan*/  async_wait; struct crypto_aead* aead_send; } ;
struct tls_sw_context_rx {int /*<<< orphan*/  strp; int /*<<< orphan*/  sk_poll; int /*<<< orphan*/  saved_data_ready; int /*<<< orphan*/ * sg_encrypted_data; int /*<<< orphan*/ * sg_aead_out; int /*<<< orphan*/  aad_space; int /*<<< orphan*/ * sg_plaintext_data; int /*<<< orphan*/ * sg_aead_in; struct crypto_aead* aead_recv; int /*<<< orphan*/  async_wait; struct crypto_aead* aead_send; } ;
struct tls_crypto_info {int cipher_type; } ;
struct cipher_context {struct tls_sw_context_tx* iv; struct tls_sw_context_tx* rec_seq; scalar_t__ tag_size; scalar_t__ rec_seq_size; scalar_t__ iv_size; scalar_t__ prepend_size; scalar_t__ overhead_size; } ;
struct TYPE_8__ {struct tls_crypto_info info; } ;
struct TYPE_7__ {struct tls_crypto_info info; } ;
struct tls_context {struct tls_sw_context_tx* priv_ctx_rx; struct tls_sw_context_tx* priv_ctx_tx; int /*<<< orphan*/  push_pending_record; struct cipher_context rx; TYPE_4__ crypto_recv; struct cipher_context tx; TYPE_3__ crypto_send; } ;
struct tls12_crypto_info_aes_gcm_128 {char* iv; char* rec_seq; char* salt; int /*<<< orphan*/  key; } ;
struct strp_callbacks {int /*<<< orphan*/  parse_msg; int /*<<< orphan*/  rcv_msg; } ;
struct sock {TYPE_2__* sk_socket; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_data_ready; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  cb ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 scalar_t__ MAX_IV_SIZE ; 
 int PTR_ERR (struct crypto_aead*) ; 
#define  TLS_CIPHER_AES_GCM_128 128 
 scalar_t__ TLS_CIPHER_AES_GCM_128_IV_SIZE ; 
 int /*<<< orphan*/  TLS_CIPHER_AES_GCM_128_KEY_SIZE ; 
 scalar_t__ TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE ; 
 scalar_t__ TLS_CIPHER_AES_GCM_128_SALT_SIZE ; 
 scalar_t__ TLS_CIPHER_AES_GCM_128_TAG_SIZE ; 
 scalar_t__ TLS_HEADER_SIZE ; 
 int crypto_aead_setauthsize (struct crypto_aead*,scalar_t__) ; 
 int crypto_aead_setkey (struct crypto_aead*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_aead* crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_init_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tls_sw_context_tx*) ; 
 struct tls_sw_context_tx* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct tls_sw_context_tx* kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tls_sw_context_tx*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct strp_callbacks*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_chain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_unmark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_check_rcv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_init (int /*<<< orphan*/ *,struct sock*,struct strp_callbacks*) ; 
 int /*<<< orphan*/  tls_data_ready ; 
 int /*<<< orphan*/  tls_queue ; 
 int /*<<< orphan*/  tls_read_size ; 
 int /*<<< orphan*/  tls_sw_push_pending_record ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int tls_set_sw_offload(struct sock *sk, struct tls_context *ctx, int tx)
{
	struct tls_crypto_info *crypto_info;
	struct tls12_crypto_info_aes_gcm_128 *gcm_128_info;
	struct tls_sw_context_tx *sw_ctx_tx = NULL;
	struct tls_sw_context_rx *sw_ctx_rx = NULL;
	struct cipher_context *cctx;
	struct crypto_aead **aead;
	struct strp_callbacks cb;
	u16 nonce_size, tag_size, iv_size, rec_seq_size;
	char *iv, *rec_seq;
	int rc = 0;

	if (!ctx) {
		rc = -EINVAL;
		goto out;
	}

	if (tx) {
		if (!ctx->priv_ctx_tx) {
			sw_ctx_tx = kzalloc(sizeof(*sw_ctx_tx), GFP_KERNEL);
			if (!sw_ctx_tx) {
				rc = -ENOMEM;
				goto out;
			}
			ctx->priv_ctx_tx = sw_ctx_tx;
		} else {
			sw_ctx_tx =
				(struct tls_sw_context_tx *)ctx->priv_ctx_tx;
		}
	} else {
		if (!ctx->priv_ctx_rx) {
			sw_ctx_rx = kzalloc(sizeof(*sw_ctx_rx), GFP_KERNEL);
			if (!sw_ctx_rx) {
				rc = -ENOMEM;
				goto out;
			}
			ctx->priv_ctx_rx = sw_ctx_rx;
		} else {
			sw_ctx_rx =
				(struct tls_sw_context_rx *)ctx->priv_ctx_rx;
		}
	}

	if (tx) {
		crypto_init_wait(&sw_ctx_tx->async_wait);
		crypto_info = &ctx->crypto_send.info;
		cctx = &ctx->tx;
		aead = &sw_ctx_tx->aead_send;
	} else {
		crypto_init_wait(&sw_ctx_rx->async_wait);
		crypto_info = &ctx->crypto_recv.info;
		cctx = &ctx->rx;
		aead = &sw_ctx_rx->aead_recv;
	}

	switch (crypto_info->cipher_type) {
	case TLS_CIPHER_AES_GCM_128: {
		nonce_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		tag_size = TLS_CIPHER_AES_GCM_128_TAG_SIZE;
		iv_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		iv = ((struct tls12_crypto_info_aes_gcm_128 *)crypto_info)->iv;
		rec_seq_size = TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE;
		rec_seq =
		 ((struct tls12_crypto_info_aes_gcm_128 *)crypto_info)->rec_seq;
		gcm_128_info =
			(struct tls12_crypto_info_aes_gcm_128 *)crypto_info;
		break;
	}
	default:
		rc = -EINVAL;
		goto free_priv;
	}

	/* Sanity-check the IV size for stack allocations. */
	if (iv_size > MAX_IV_SIZE || nonce_size > MAX_IV_SIZE) {
		rc = -EINVAL;
		goto free_priv;
	}

	cctx->prepend_size = TLS_HEADER_SIZE + nonce_size;
	cctx->tag_size = tag_size;
	cctx->overhead_size = cctx->prepend_size + cctx->tag_size;
	cctx->iv_size = iv_size;
	cctx->iv = kmalloc(iv_size + TLS_CIPHER_AES_GCM_128_SALT_SIZE,
			   GFP_KERNEL);
	if (!cctx->iv) {
		rc = -ENOMEM;
		goto free_priv;
	}
	memcpy(cctx->iv, gcm_128_info->salt, TLS_CIPHER_AES_GCM_128_SALT_SIZE);
	memcpy(cctx->iv + TLS_CIPHER_AES_GCM_128_SALT_SIZE, iv, iv_size);
	cctx->rec_seq_size = rec_seq_size;
	cctx->rec_seq = kmemdup(rec_seq, rec_seq_size, GFP_KERNEL);
	if (!cctx->rec_seq) {
		rc = -ENOMEM;
		goto free_iv;
	}

	if (sw_ctx_tx) {
		sg_init_table(sw_ctx_tx->sg_encrypted_data,
			      ARRAY_SIZE(sw_ctx_tx->sg_encrypted_data));
		sg_init_table(sw_ctx_tx->sg_plaintext_data,
			      ARRAY_SIZE(sw_ctx_tx->sg_plaintext_data));

		sg_init_table(sw_ctx_tx->sg_aead_in, 2);
		sg_set_buf(&sw_ctx_tx->sg_aead_in[0], sw_ctx_tx->aad_space,
			   sizeof(sw_ctx_tx->aad_space));
		sg_unmark_end(&sw_ctx_tx->sg_aead_in[1]);
		sg_chain(sw_ctx_tx->sg_aead_in, 2,
			 sw_ctx_tx->sg_plaintext_data);
		sg_init_table(sw_ctx_tx->sg_aead_out, 2);
		sg_set_buf(&sw_ctx_tx->sg_aead_out[0], sw_ctx_tx->aad_space,
			   sizeof(sw_ctx_tx->aad_space));
		sg_unmark_end(&sw_ctx_tx->sg_aead_out[1]);
		sg_chain(sw_ctx_tx->sg_aead_out, 2,
			 sw_ctx_tx->sg_encrypted_data);
	}

	if (!*aead) {
		*aead = crypto_alloc_aead("gcm(aes)", 0, 0);
		if (IS_ERR(*aead)) {
			rc = PTR_ERR(*aead);
			*aead = NULL;
			goto free_rec_seq;
		}
	}

	ctx->push_pending_record = tls_sw_push_pending_record;

	rc = crypto_aead_setkey(*aead, gcm_128_info->key,
				TLS_CIPHER_AES_GCM_128_KEY_SIZE);
	if (rc)
		goto free_aead;

	rc = crypto_aead_setauthsize(*aead, cctx->tag_size);
	if (rc)
		goto free_aead;

	if (sw_ctx_rx) {
		/* Set up strparser */
		memset(&cb, 0, sizeof(cb));
		cb.rcv_msg = tls_queue;
		cb.parse_msg = tls_read_size;

		strp_init(&sw_ctx_rx->strp, sk, &cb);

		write_lock_bh(&sk->sk_callback_lock);
		sw_ctx_rx->saved_data_ready = sk->sk_data_ready;
		sk->sk_data_ready = tls_data_ready;
		write_unlock_bh(&sk->sk_callback_lock);

		sw_ctx_rx->sk_poll = sk->sk_socket->ops->poll;

		strp_check_rcv(&sw_ctx_rx->strp);
	}

	goto out;

free_aead:
	crypto_free_aead(*aead);
	*aead = NULL;
free_rec_seq:
	kfree(cctx->rec_seq);
	cctx->rec_seq = NULL;
free_iv:
	kfree(cctx->iv);
	cctx->iv = NULL;
free_priv:
	if (tx) {
		kfree(ctx->priv_ctx_tx);
		ctx->priv_ctx_tx = NULL;
	} else {
		kfree(ctx->priv_ctx_rx);
		ctx->priv_ctx_rx = NULL;
	}
out:
	return rc;
}