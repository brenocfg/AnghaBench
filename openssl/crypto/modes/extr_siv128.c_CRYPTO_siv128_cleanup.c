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
struct TYPE_3__ {int final_ret; int crypto_ok; int /*<<< orphan*/  tag; int /*<<< orphan*/  d; int /*<<< orphan*/ * mac; int /*<<< orphan*/ * mac_ctx_init; int /*<<< orphan*/ * cipher_ctx; } ;
typedef  TYPE_1__ SIV128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 

int CRYPTO_siv128_cleanup(SIV128_CONTEXT *ctx)
{
    if (ctx != NULL) {
        EVP_CIPHER_CTX_free(ctx->cipher_ctx);
        ctx->cipher_ctx = NULL;
        EVP_MAC_CTX_free(ctx->mac_ctx_init);
        ctx->mac_ctx_init = NULL;
        EVP_MAC_free(ctx->mac);
        ctx->mac = NULL;
        OPENSSL_cleanse(&ctx->d, sizeof(ctx->d));
        OPENSSL_cleanse(&ctx->tag, sizeof(ctx->tag));
        ctx->final_ret = -1;
        ctx->crypto_ok = 1;
    }
    return 1;
}