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
struct TYPE_3__ {int /*<<< orphan*/  seedlen; int /*<<< orphan*/  seed; int /*<<< orphan*/  seclen; int /*<<< orphan*/  sec; int /*<<< orphan*/  P_sha1; int /*<<< orphan*/  P_hash; } ;
typedef  TYPE_1__ TLS1_PRF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kdf_tls1_prf_reset(void *vctx)
{
    TLS1_PRF *ctx = (TLS1_PRF *)vctx;

    EVP_MAC_CTX_free(ctx->P_hash);
    EVP_MAC_CTX_free(ctx->P_sha1);
    OPENSSL_clear_free(ctx->sec, ctx->seclen);
    OPENSSL_cleanse(ctx->seed, ctx->seedlen);
    memset(ctx, 0, sizeof(*ctx));
}