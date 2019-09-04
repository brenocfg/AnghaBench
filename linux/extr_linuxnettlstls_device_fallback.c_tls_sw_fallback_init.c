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
struct tls_offload_context_tx {int /*<<< orphan*/ * aead_send; } ;
struct tls_crypto_info {int dummy; } ;
struct tls12_crypto_info_aes_gcm_128 {int /*<<< orphan*/ * key; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLS_CIPHER_AES_GCM_128_KEY_SIZE ; 
 int /*<<< orphan*/  TLS_CIPHER_AES_GCM_128_TAG_SIZE ; 
 int crypto_aead_setauthsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_aead_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int) ; 

int tls_sw_fallback_init(struct sock *sk,
			 struct tls_offload_context_tx *offload_ctx,
			 struct tls_crypto_info *crypto_info)
{
	const u8 *key;
	int rc;

	offload_ctx->aead_send =
	    crypto_alloc_aead("gcm(aes)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(offload_ctx->aead_send)) {
		rc = PTR_ERR(offload_ctx->aead_send);
		pr_err_ratelimited("crypto_alloc_aead failed rc=%d\n", rc);
		offload_ctx->aead_send = NULL;
		goto err_out;
	}

	key = ((struct tls12_crypto_info_aes_gcm_128 *)crypto_info)->key;

	rc = crypto_aead_setkey(offload_ctx->aead_send, key,
				TLS_CIPHER_AES_GCM_128_KEY_SIZE);
	if (rc)
		goto free_aead;

	rc = crypto_aead_setauthsize(offload_ctx->aead_send,
				     TLS_CIPHER_AES_GCM_128_TAG_SIZE);
	if (rc)
		goto free_aead;

	return 0;
free_aead:
	crypto_free_aead(offload_ctx->aead_send);
err_out:
	return rc;
}