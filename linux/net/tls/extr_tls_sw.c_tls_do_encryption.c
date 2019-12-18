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
typedef  int /*<<< orphan*/  u32 ;
struct tls_sw_context_tx {struct tls_rec* open_rec; int /*<<< orphan*/  encrypt_pending; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  aead_send; } ;
struct TYPE_3__ {int /*<<< orphan*/  curr; } ;
struct sk_msg {TYPE_1__ sg; } ;
struct tls_rec {int /*<<< orphan*/  list; int /*<<< orphan*/  tx_ready; int /*<<< orphan*/ * iv_data; int /*<<< orphan*/  sg_aead_out; int /*<<< orphan*/  sg_aead_in; struct sk_msg msg_encrypted; } ;
struct tls_prot_info {scalar_t__ cipher_type; scalar_t__ prepend_size; int /*<<< orphan*/  aad_size; int /*<<< orphan*/  version; scalar_t__ salt_size; scalar_t__ iv_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  rec_seq; int /*<<< orphan*/  iv; } ;
struct tls_context {TYPE_2__ tx; struct tls_prot_info prot_info; } ;
struct sock {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct list_head {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  TLS_AES_CCM_IV_B0_BYTE ; 
 scalar_t__ TLS_CIPHER_AES_CCM_128 ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_advance_record_sn (struct sock*,struct tls_prot_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  tls_encrypt_done ; 
 int /*<<< orphan*/  xor_iv_with_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_do_encryption(struct sock *sk,
			     struct tls_context *tls_ctx,
			     struct tls_sw_context_tx *ctx,
			     struct aead_request *aead_req,
			     size_t data_len, u32 start)
{
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	struct tls_rec *rec = ctx->open_rec;
	struct sk_msg *msg_en = &rec->msg_encrypted;
	struct scatterlist *sge = sk_msg_elem(msg_en, start);
	int rc, iv_offset = 0;

	/* For CCM based ciphers, first byte of IV is a constant */
	if (prot->cipher_type == TLS_CIPHER_AES_CCM_128) {
		rec->iv_data[0] = TLS_AES_CCM_IV_B0_BYTE;
		iv_offset = 1;
	}

	memcpy(&rec->iv_data[iv_offset], tls_ctx->tx.iv,
	       prot->iv_size + prot->salt_size);

	xor_iv_with_seq(prot->version, rec->iv_data, tls_ctx->tx.rec_seq);

	sge->offset += prot->prepend_size;
	sge->length -= prot->prepend_size;

	msg_en->sg.curr = start;

	aead_request_set_tfm(aead_req, ctx->aead_send);
	aead_request_set_ad(aead_req, prot->aad_size);
	aead_request_set_crypt(aead_req, rec->sg_aead_in,
			       rec->sg_aead_out,
			       data_len, rec->iv_data);

	aead_request_set_callback(aead_req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  tls_encrypt_done, sk);

	/* Add the record in tx_list */
	list_add_tail((struct list_head *)&rec->list, &ctx->tx_list);
	atomic_inc(&ctx->encrypt_pending);

	rc = crypto_aead_encrypt(aead_req);
	if (!rc || rc != -EINPROGRESS) {
		atomic_dec(&ctx->encrypt_pending);
		sge->offset -= prot->prepend_size;
		sge->length += prot->prepend_size;
	}

	if (!rc) {
		WRITE_ONCE(rec->tx_ready, true);
	} else if (rc != -EINPROGRESS) {
		list_del(&rec->list);
		return rc;
	}

	/* Unhook the record from context if encryption is not failure */
	ctx->open_rec = NULL;
	tls_advance_record_sn(sk, prot, &tls_ctx->tx);
	return rc;
}