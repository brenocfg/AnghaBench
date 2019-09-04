#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_sw_context_tx {TYPE_1__* sg_encrypted_data; int /*<<< orphan*/  async_wait; int /*<<< orphan*/  sg_aead_out; int /*<<< orphan*/  sg_aead_in; int /*<<< orphan*/  aead_send; } ;
struct TYPE_4__ {scalar_t__ prepend_size; int /*<<< orphan*/  iv; } ;
struct tls_context {TYPE_2__ tx; } ;
struct aead_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  TLS_AAD_SPACE_SIZE ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_encrypt (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_do_encryption(struct tls_context *tls_ctx,
			     struct tls_sw_context_tx *ctx,
			     struct aead_request *aead_req,
			     size_t data_len)
{
	int rc;

	ctx->sg_encrypted_data[0].offset += tls_ctx->tx.prepend_size;
	ctx->sg_encrypted_data[0].length -= tls_ctx->tx.prepend_size;

	aead_request_set_tfm(aead_req, ctx->aead_send);
	aead_request_set_ad(aead_req, TLS_AAD_SPACE_SIZE);
	aead_request_set_crypt(aead_req, ctx->sg_aead_in, ctx->sg_aead_out,
			       data_len, tls_ctx->tx.iv);

	aead_request_set_callback(aead_req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  crypto_req_done, &ctx->async_wait);

	rc = crypto_wait_req(crypto_aead_encrypt(aead_req), &ctx->async_wait);

	ctx->sg_encrypted_data[0].offset -= tls_ctx->tx.prepend_size;
	ctx->sg_encrypted_data[0].length += tls_ctx->tx.prepend_size;

	return rc;
}