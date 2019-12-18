#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; int /*<<< orphan*/  xcghash_len; int /*<<< orphan*/  xcghash; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_SSHKDF ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kdf_sshkdf_reset(void *vctx)
{
    KDF_SSHKDF *ctx = (KDF_SSHKDF *)vctx;

    ossl_prov_digest_reset(&ctx->digest);
    OPENSSL_clear_free(ctx->key, ctx->key_len);
    OPENSSL_clear_free(ctx->xcghash, ctx->xcghash_len);
    OPENSSL_clear_free(ctx->session_id, ctx->session_id_len);
    memset(ctx, 0, sizeof(*ctx));
}