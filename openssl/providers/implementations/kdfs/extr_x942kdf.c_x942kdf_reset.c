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
struct TYPE_3__ {int /*<<< orphan*/  ukm_len; int /*<<< orphan*/  ukm; int /*<<< orphan*/  secret_len; int /*<<< orphan*/  secret; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_X942 ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x942kdf_reset(void *vctx)
{
    KDF_X942 *ctx = (KDF_X942 *)vctx;

    ossl_prov_digest_reset(&ctx->digest);
    OPENSSL_clear_free(ctx->secret, ctx->secret_len);
    OPENSSL_clear_free(ctx->ukm, ctx->ukm_len);
    memset(ctx, 0, sizeof(*ctx));
}