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
struct TYPE_3__ {int /*<<< orphan*/  constant_len; int /*<<< orphan*/  constant; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  cipher; } ;
typedef  TYPE_1__ KRB5KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_cipher_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void krb5kdf_reset(void *vctx)
{
    KRB5KDF_CTX *ctx = (KRB5KDF_CTX *)vctx;

    ossl_prov_cipher_reset(&ctx->cipher);
    OPENSSL_clear_free(ctx->key, ctx->key_len);
    OPENSSL_clear_free(ctx->constant, ctx->constant_len);
    memset(ctx, 0, sizeof(*ctx));
}