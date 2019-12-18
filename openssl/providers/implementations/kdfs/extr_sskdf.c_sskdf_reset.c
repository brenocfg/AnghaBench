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
struct TYPE_3__ {int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  secret_len; int /*<<< orphan*/  secret; int /*<<< orphan*/  digest; int /*<<< orphan*/  macctx; } ;
typedef  TYPE_1__ KDF_SSKDF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sskdf_reset(void *vctx)
{
    KDF_SSKDF *ctx = (KDF_SSKDF *)vctx;

    EVP_MAC_CTX_free(ctx->macctx);
    ossl_prov_digest_reset(&ctx->digest);
    OPENSSL_clear_free(ctx->secret, ctx->secret_len);
    OPENSSL_clear_free(ctx->info, ctx->info_len);
    OPENSSL_clear_free(ctx->salt, ctx->salt_len);
    memset(ctx, 0, sizeof(*ctx));
}