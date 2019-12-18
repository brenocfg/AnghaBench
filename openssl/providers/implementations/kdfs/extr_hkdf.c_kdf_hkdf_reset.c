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
struct TYPE_3__ {int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  salt; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_HKDF ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kdf_hkdf_reset(void *vctx)
{
    KDF_HKDF *ctx = (KDF_HKDF *)vctx;

    ossl_prov_digest_reset(&ctx->digest);
    OPENSSL_free(ctx->salt);
    OPENSSL_clear_free(ctx->key, ctx->key_len);
    OPENSSL_cleanse(ctx->info, ctx->info_len);
    memset(ctx, 0, sizeof(*ctx));
}