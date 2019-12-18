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
struct TYPE_2__ {struct krb5_ctx* data; } ;
struct krb5_ctx {TYPE_1__ mech_used; int /*<<< orphan*/  initiator_enc_aux; int /*<<< orphan*/  acceptor_enc_aux; int /*<<< orphan*/  initiator_enc; int /*<<< orphan*/  acceptor_enc; int /*<<< orphan*/  enc; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct krb5_ctx*) ; 

__attribute__((used)) static void
gss_delete_sec_context_kerberos(void *internal_ctx) {
	struct krb5_ctx *kctx = internal_ctx;

	crypto_free_sync_skcipher(kctx->seq);
	crypto_free_sync_skcipher(kctx->enc);
	crypto_free_sync_skcipher(kctx->acceptor_enc);
	crypto_free_sync_skcipher(kctx->initiator_enc);
	crypto_free_sync_skcipher(kctx->acceptor_enc_aux);
	crypto_free_sync_skcipher(kctx->initiator_enc_aux);
	kfree(kctx->mech_used.data);
	kfree(kctx);
}