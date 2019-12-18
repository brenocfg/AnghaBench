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
struct TYPE_3__ {int /*<<< orphan*/  ccm_ctx; int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ PROV_CCM_CTX ;

/* Variables and functions */
 scalar_t__ CRYPTO_ccm128_decrypt (int /*<<< orphan*/ *,unsigned char const*,unsigned char*,size_t) ; 
 scalar_t__ CRYPTO_ccm128_decrypt_ccm64 (int /*<<< orphan*/ *,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_ccm128_tag (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 

int ccm_generic_auth_decrypt(PROV_CCM_CTX *ctx, const unsigned char *in,
                             unsigned char *out, size_t len,
                             unsigned char *expected_tag, size_t taglen)
{
    int rv = 0;

    if (ctx->str != NULL)
        rv = CRYPTO_ccm128_decrypt_ccm64(&ctx->ccm_ctx, in, out, len,
                                         ctx->str) == 0;
    else
        rv = CRYPTO_ccm128_decrypt(&ctx->ccm_ctx, in, out, len) == 0;
    if (rv) {
        unsigned char tag[16];

        if (!CRYPTO_ccm128_tag(&ctx->ccm_ctx, tag, taglen)
            || CRYPTO_memcmp(tag, expected_tag, taglen) != 0)
            rv = 0;
    }
    if (rv == 0)
        OPENSSL_cleanse(out, len);
    return rv;
}